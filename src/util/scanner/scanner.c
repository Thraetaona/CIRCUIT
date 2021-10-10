// This file is part of CIRCUIT.
// 
// CIRCUIT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// CIRCUIT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CIRCUIT.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

extern int errno; // Declared in <errno.h>


// This function "scans" (Reads) the contents of a supplied file into a buffer (An arrays of bytes with a dynamic size) in the memory.
// 
// The only parameter it takes is a pointer to a constant character/array. (Same as fopen()'s filename parameter.)
// 
// Returns a pointer to said buffer on success, otherwise If any error occurs during 
// this process, it will print them out to stderr and return early with NULL (0).
// 
// It is up to the caller to free up the memory allocated by this.
char *scan_into_buffer(const char *filename) {
    errno = 0; // Setting the flag variable errno to 0 indicates "no errors", so that a previously set value won't affect us.

    // This opens the specified file in read-only binary mode (For Windows compatibility mainly, as the mode does not affect POSIX).
    // For windows or systems that use more than one character (For example '\r\n') to represent "newlines", 
    // '\n' newlines are automatically translated to '\r\n' in text mode, but that is not the case with binary mode.
    FILE *const file_descriptor = fopen(filename, "rb");

    // Checks if the given file even exists, if it does not then we'll skip the next steps and return early.
    if (file_descriptor == NULL) // fopen() returns NULL (0) on failure.
        goto cleanup;

    // After opening the file we have to measure its total size and allocate the buffer accordingly.
    // In order to do this we first have to know the byte position (offset) of the very last character in the file.
    // 
    // We could also use fstat() here instead, but that would only work on UNIX (POSIX) and not Windows.
    if (fseek(file_descriptor, 0L, SEEK_END) != 0) // fseek() returns 0 on success. (Any value other than 0 on failure.)
        goto cleanup;
    
    // After fseek points to the file's end, we can use ftell to get it's offset.
    const size_t buffer_length = ftell(file_descriptor); // Total size (length) of the opened file in bytes (char).
    if (buffer_length == -1) // ftell() returns -1 on failure.
        goto cleanup;

    // Here we allocate a total of bytes equal to `buffer_length` plus one extra byte for the null '\0' terminator. (Since EOF != null)
    char *result_buffer = malloc(sizeof(char) * (buffer_length + 1));
    if (result_buffer == NULL)
        goto cleanup;

    // Now that we have a large enough buffer we can go back to the beginning of the file and start copying its contents there.
    // fseek() with an offset of 0 and SEEK_SET whence, does the same as rewind(); but the latter does not have any return value.
    if (fseek(file_descriptor, 0L, SEEK_SET) != 0)
        goto cleanup;

    // Lastly we can read the entire file into our newly allocated buffer.  We also assign the return value of fread() to
    // a variable so that we can use that if its required later instead of calling strlen() everytime.
    // 
    // Also if the number of bytes read does not equal the file size we've previously calculated then we'll return early.
    const size_t bytes_read = fread(result_buffer, sizeof (char), buffer_length, file_descriptor);
    if (ferror(file_descriptor) != 0) // ferror() returns a non-zero value on failure.
        goto cleanup;

    // Appends a terminating null character to the end of our buffer as files use the end-of-file character and not null like strings do.
    // This is more efficient than using calloc() (Which is basically malloc() plus zero'ing _all_ the allocated memory regions).
    result_buffer[bytes_read+1] = '\0'; // bytes_read++ would also alter bytes_read, so +1 is the reasonable choice here.
    

cleanup:
    // (If any) Will Print the error code along with it's error message to stderr.
    if (errno != 0) {
        fprintf(stderr, "Error number `%d` in file `%s` was encountered: \"%s\"\n ", errno, filename, strerror(errno));
        clearerr(file_descriptor);
    }

    // Return early and skip calling fclose() afterwards, if we were not able to open any file in the first place.
    if (file_descriptor == NULL) {
        return NULL;
    }

    // We are finally done working with the file, so we should close the handle that we've opened earlier.
    if (fclose(file_descriptor) != 0) { // fclose() returns 0 on success.  It should generally not fail.
        perror("fclose() failed");
        clearerr(file_descriptor);
        // Well, if it does fail, then we should not continue to retry (As that would result in undefined behavior) and just return.
    }

    if (result_buffer != NULL && bytes_read == buffer_length) {
        // By now we are sure that no errors were encountered and that the file was fully scanned, so we can return the requested buffer.
        return result_buffer;
    }
    else if (bytes_read != buffer_length) { // We somehow (e.g., File was edited) read less (Not more or equal) bytes than we were supposed to.
        perror("The specified file was only partially read");
        clearerr(file_descriptor);
    }
    
    // By this point opening the file itself was successful, however, a problem (Which we have handled above) occured in one of the later steps.
    return NULL;
}