#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define BUFFER_SIZE 2048

// Forward declaration of the write_data function
static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

void api(const char *path) {
    CURL *curl;
    CURLcode res;
    char *ip_address = "64.227.121.226";
    int port = 3000;
    char url[256];

    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize a CURL handle
    curl = curl_easy_init();
    if (curl) {
        // Construct the full URL for the API call
        snprintf(url, sizeof(url), "http://%s:%d%s", ip_address, port, path);

        // Set the URL and other options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup CURL globally
    curl_global_cleanup();
}

char *api_json(const char *path) {
    CURL *curl;
    CURLcode res;
    char *ip_address = "64.227.121.226";
    int port = 3000;
    char url[256];
    char *response = NULL;

    // Initialize CURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize a CURL handle
    curl = curl_easy_init();
    if (curl) {
        // Construct the full URL for the API call
        snprintf(url, sizeof(url), "http://%s:%d%s", ip_address, port, path);

        // Set the URL and other options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(response);
            response = NULL;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup CURL globally
    curl_global_cleanup();

    return response; // The caller is responsible for freeing this memory
}

// This function will be called by libcurl as soon as there is data received that needs to be saved
static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    // Calculate the real size of the incoming buffer
    size_t real_size = size * nmemb;

    // Allocate memory for the buffer
    char **response_ptr = (char **)userp;
    *response_ptr = realloc(*response_ptr, real_size + 1);

    if (*response_ptr == NULL) {
        // out of memory!
        fprintf(stderr, "not enough memory (realloc returned NULL)\n");
        return 0;
    }

    // Copy the buffer to the new memory space
    memcpy(*response_ptr, buffer, real_size);

    // Null-terminate the result
    (*response_ptr)[real_size] = '\0';

    // Return the real size of the buffer
    return real_size;
}