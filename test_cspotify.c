/*******************************************************************************
> CSpotify - 20T3 COMP1511 Assignment 2
| test_cspotify.c
|
| zID: <YOUR-ZID-HERE>
| Name: <YOUR-NAME-HERE>
| Date: <DATE-HERE>
|
| Version 1.0.0: Assignment released.
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_cspotify.h"
#include "cspotify.h"
#include "capture.h"

/*********************************************
> Test Functions
| These tests are explained in test_cspotify.h
*********************************************/

/*********
> STAGE 1
*********/

// Test function for 'add_playlist'
void test_add_playlist(void) {

    // Test 1: Does add_playlist return SUCCESS and add 
    // when adding one Playlist with a valid name?
    Library testLibrary = create_library();

    int result = add_playlist(testLibrary, "Favourites");
    if (result != SUCCESS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    char printText[10000];
    CAPTURE(print_library(testLibrary), printText, 10000);
    if (!string_contains(printText, "Favourites")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 2: Does add_playlist return ERROR_INVALID_INPUTS
    // and not add the playlist into the Library
    // when trying to add a Playlist with an invalid name?
    // TODO: Add your test for Test 2
    result = add_playlist(testLibrary, "PopSong");
    result = add_playlist(testLibrary, "May'sLike");
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }


    CAPTURE(print_library(testLibrary), printText, 10000);
    if (!string_contains(printText, "PopSong")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    if (string_contains(printText, "May'sLike")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 3: ???
    // TODO: Add your own test, and explain it.

    printf("MEETS SPEC\n");
}

// Test function for 'rename_playlist'
void test_rename_playlist(void) {
    // Test 1: Does rename_playlist return ERROR_NOT_FOUND 
    // when trying to rename a playlist when the Library is empty
    Library testLibrary = create_library();

    int result = rename_playlist(testLibrary, "Favourites", "Dislikes");
    if (result != ERROR_NOT_FOUND) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 2: Does rename_playlist successfully
    // rename a Playlist
    // when a valid new Playlist name is given to 
    // rename an existing Playlist in the Library?
    // TODO: Add your test for Test 2
    result = add_playlist(testLibrary, "Favourites");
    result = rename_playlist(testLibrary, "Favourites", "Dislikes");
    result = rename_playlist(testLibrary, "Dislikes", "My_Dislikes");
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 3: ???
    // TODO: Add your own test, and explain it.

    printf("MEETS SPEC\n");
}


/*********
> STAGE 2
*********/

// Test function for 'add_track'
void test_add_track(void) {
    // Test 1: Does add_track successfully add 
    // multiple (more than 3 Tracks) Tracks 
    // to the Library?
    // TODO: Add your test for Test 1
    Library testLibrary = create_library();
    int result = add_track(testLibrary, "LoveStory", "TaylorSwift", 230, 0);

    if (result != ERROR_NOT_FOUND) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    
    result = add_playlist(testLibrary, "Favourites");
    result = add_playlist(testLibrary, "RoadTrip");

    result = add_track(testLibrary, "LoveStory", "TaylorSwift", 230, 0);
    result = add_track(testLibrary, "LoveStory", "TaylorSwift", 230, 1);
    if (result != SUCCESS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    select_next_playlist(testLibrary);
    result = add_track(testLibrary, "Dynamic", "BTS", 50, 0);

    char printText[10000];
    CAPTURE(print_library(testLibrary), printText, 10000);
    if (!string_contains(printText, 
       "- LoveStory                           TaylorSwift                 03:50\n       - LoveStory                           TaylorSwift                 03:50")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    if (!string_contains(printText, 
        "- Dynamic                             BTS                         00:50")) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    // Test 2: Does add_track successfully add invalid inputs Tracks
    // TODO: Add your own test, and explain it.
    result = add_track(testLibrary, "Love Story", "TaylorSwift", 230, 0);
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    result = add_track(testLibrary, "LoveStory", "Taylor Swift", 230, 0);
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    result = add_track(testLibrary, "LoveStory", "TaylorSwift", 230, -1);
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    result = add_track(testLibrary, "LoveStory", "TaylorSwift", 230, 3);
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    result = add_track(testLibrary, "Love Story", "TaylorSwift", -1, 0);
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    result = add_track(testLibrary, "Love Story", "TaylorSwift", 0, 0);
    if (result != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    printf("MEETS SPEC\n");
}

// Test function for 'playlist_length'
void test_playlist_length(void) {
    // Test 1: Does playlist_length work for Tracks 
    // with lengths greater than 60 seconds?
    // TODO: Add your test for Test 1
    Library testLibrary = create_library();
    int minutes, seconds;
    playlist_length(testLibrary, &minutes, &seconds);
    if (minutes != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    if (seconds != ERROR_INVALID_INPUTS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    // Test 2: ???
    // TODO: Add your own test, and explain it.
    int result = add_playlist(testLibrary, "Favourites");
    if (result != SUCCESS) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    playlist_length(testLibrary, &minutes, &seconds);
    if (minutes != 0) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    if (seconds != 0) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    result = add_track(testLibrary, "LoveStory", "TaylorSwift", 30, 0);
    result = add_track(testLibrary, "LoveStory", "TaylorSwift", 30, 0);

    playlist_length(testLibrary, &minutes, &seconds);
    if (minutes != 1) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }
    if (seconds != 0) {
        printf("DOES NOT MEET SPEC\n");
        return;
    }

    printf("MEETS SPEC\n");
}


/*********
> STAGE 3
*********/

// Test function for 'delete_playlist'
void test_delete_playlist(void) {
    // Test 1: Does delete_playlist work if
    // the selected Playlist is the first Playlist
    // in the Library?
    // TODO: Add your test for Test 1

    // Test 2: ???
    // TODO: Add your own test, and explain it.

    printf("MEETS SPEC\n");
}


/*********
> STAGE 4
*********/

// Test function for 'soundex_search'
void test_soundex_search(void) {
    // Test 1: ???
    // TODO: Add your own test, and explain it.

    // Test 2: ???
    // TODO: Add your own test, and explain it.

    printf("MEETS SPEC\n");
}


/*********
> EXTRA
*********/

//  Your extra tests (Not worth marks)
void extra_tests(void) {
    // TODO: Add any extra tests you have here
    printf("MEETS SPEC\n");
}

/*****************
> Helper Functions
*****************/

// Find the string 'needle' in 'haystack'
int string_contains(char *haystack, char *needle) {
    return strstr(haystack, needle) != NULL;
}
