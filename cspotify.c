/*******************************************************************************
> CSpotify - 20T3 COMP1511 Assignment 2
| cspotify.c
|
| zID: z5119623
| Name: Meisi Li
| Date: 08/11/2020
| Program Description:
| <INSERT DESCRIPTION>
|
| Version 1.0.0: Assignment released.
|
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cspotify.h"

/******************************************************************************/
// TODO: Add any other #defines you need.
#define PLAYLIST_EXIST 1
#define PLAYLIST_NOT_EXIST 2
#define SELECTED 3
#define NOT_SELECTED 4
#define UNRENAMED 5
#define RENAMED 6
#define UNFLAGED 7
#define FLAGED 8


/******************************************************************************/
// 'struct library' represents a library, which represents the state of the
// entire program. It is mainly used to point to a linked list of 
// playlists, though you may want to add other fields to it.
//
// You may choose to add or change fields in this struct.
struct library {
    struct playlist *head;
};

// 'struct playlist' represents a playlist. 
// You may choose to add or change fields in this struct.
struct playlist {
    char name[MAX_LEN];
    struct track *tracks;
    struct playlist *next;
    int selected;
    int num_track;
};

// 'struct trackLength' represents the length of a track. 
// You may choose to add or change fields in this struct.
struct trackLength {
    int minutes;
    int seconds;
};

// 'struct track' represents a track. 
// You may choose to add or change fields in this struct.
struct track {
    char title[MAX_LEN];
    char artist[MAX_LEN];
    struct trackLength length;
    struct track *next;
};

/******************************************************************************/
// TODO: Add any other structs you define here.


/******************************************************************************/
// TODO: Add prototypes for any extra functions you create here.

// Function prototypes for helper functions. 
static void print_playlist(int number, char playlistName[MAX_LEN]);
static void print_selected_playlist(int number, char playlistName[MAX_LEN]);
static void print_track(char title[MAX_LEN], char artist[MAX_LEN], int minutes, int seconds);
static int checkNameValid(char playlistName[MAX_LEN]);



/******************************************************************************/
// You need to implement the following functions.
// In other words, write code to make the function work as described 
// in cspotify.h

/*********
> STAGE 1
*********/

// Create a new Library and return a pointer to it.
Library create_library(void) {
    Library newLibrary = malloc(sizeof(struct library));
    newLibrary->head = NULL;
    return newLibrary;
}

static int checkNameValid(char playlistName[MAX_LEN]) {
    int len = strlen(playlistName);
    int i = 0;
    while (i < len) {
        if (playlistName[i] < '0') {
            return ERROR_INVALID_INPUTS;
        } else if (playlistName[i] > '9' && playlistName[i] < 'A') {
            return ERROR_INVALID_INPUTS;
        } else if (playlistName[i] > 'Z' && playlistName[i] < 'a') {
            return ERROR_INVALID_INPUTS;
        } else if (playlistName[i] > 'z') {
            return ERROR_INVALID_INPUTS;
        }
        i++;
    }
    return SUCCESS;
}

// Add a new Playlist to the Library.
int add_playlist(Library library, char playlistName[MAX_LEN]) {
    Playlist new_playlist = malloc(sizeof (struct playlist));
    
    // store the context in the new playlist
    if (playlistName == NULL)   return ERROR_INVALID_INPUTS;
    if (checkNameValid(playlistName) == ERROR_INVALID_INPUTS)
        return ERROR_INVALID_INPUTS;

    strcpy(new_playlist->name, playlistName);
    new_playlist->tracks = NULL;
    new_playlist->next = NULL;

    new_playlist->num_track = 0;

    // insert the new playlist at the end of the library 
    Playlist curr_pl = library->head;
    if (curr_pl != NULL) {
        new_playlist->selected = NOT_SELECTED;
        int flag = PLAYLIST_NOT_EXIST;
        while (curr_pl->next != NULL) {
            if (strcmp(curr_pl->name, playlistName) == 0)   flag = PLAYLIST_EXIST;
            curr_pl = curr_pl->next;
        }
        if (flag == PLAYLIST_NOT_EXIST) curr_pl->next = new_playlist;
    } else {
        new_playlist->selected = SELECTED;
        library->head = new_playlist;
    }
    
    return SUCCESS;
}

// Print out the Library.
void print_library(Library library) {
    if (library != NULL) {
        int i = 0;
        Playlist curr_pl = library->head;
        while (curr_pl != NULL) {
            if (curr_pl->selected == SELECTED) {
                print_selected_playlist(i, curr_pl->name);
            } else {
                print_playlist(i, curr_pl->name);
            }
            Track curr_track = curr_pl->tracks;
            while (curr_track != NULL) {
                int minutes = curr_track->length.minutes;
                int seconds = curr_track->length.seconds;
                print_track(curr_track->title, 
                    curr_track->artist, minutes, seconds);
                curr_track = curr_track->next;
            }
            curr_pl = curr_pl->next;
            i++;
        }
    }
}

// Rename the name of an existing Playlist.
int rename_playlist(Library library, char playlistName[MAX_LEN],
    char newPlaylistName[MAX_LEN]) {
    if (newPlaylistName == NULL)    return ERROR_INVALID_INPUTS;
    if (checkNameValid(newPlaylistName) == ERROR_INVALID_INPUTS)
        return ERROR_INVALID_INPUTS;

    Playlist curr_pl = library->head;

    int flag = UNRENAMED;
    while (curr_pl != NULL) {
        if (strcmp(playlistName, curr_pl->name) == 0) {
            strcpy(curr_pl->name, newPlaylistName);
            flag = RENAMED;
        }
        curr_pl = curr_pl->next;
    }
    if (flag == UNRENAMED)  return ERROR_NOT_FOUND;
    return SUCCESS;
}


/*********
> STAGE 2
*********/

// Selects the next Playlist in the Library.
void select_next_playlist(Library library) {
    Playlist curr = library->head;
    int flag = NOT_SELECTED;
    while (curr != NULL && flag == NOT_SELECTED) {
        if (curr->selected == SELECTED) {
            curr->selected = NOT_SELECTED;
            if (curr->next != NULL) {
                curr->next->selected = SELECTED;
            } else {
                library->head->selected = SELECTED;
            }
            flag = SELECTED;
        }
        curr = curr->next;
    }
}

// Selects the previous Playlist in the Library.
void select_previous_playlist(Library library) {
    int flag = NOT_SELECTED;
    Playlist curr = library->head;
    if (curr != NULL) {
        while (curr->next != NULL && flag == NOT_SELECTED) {
            if (curr->next->selected == SELECTED) {
                curr->next->selected = NOT_SELECTED;
                curr->selected = SELECTED;
                flag = SELECTED;
            }
            curr = curr->next;
        }
        if (library->head->selected == SELECTED && flag == NOT_SELECTED) {
            library->head->selected = NOT_SELECTED;
            curr->selected = SELECTED;
            flag = SELECTED;
        }
    }
}

static Playlist getSelected(Library library) {
    Playlist curr = library->head;
    while (curr != NULL) {
    // while (curr->selected != SELECTED && curr != NULL) {
        if (curr->selected == SELECTED) return curr;
        curr = curr->next;
    }
    return curr;
}

// Add a new Track to the selected Playlist.
int add_track(Library library, char title[MAX_LEN], char artist[MAX_LEN], 
    int trackLengthInSec, int position) {

    // get the selected playlist 
    Playlist selected_list = getSelected(library);

    if (selected_list == NULL)  return ERROR_NOT_FOUND;

    // check the input valid 
    if (position < 0 || position > selected_list->num_track)  
        return ERROR_INVALID_INPUTS;
    if (checkNameValid(title) == ERROR_INVALID_INPUTS)
        return ERROR_INVALID_INPUTS;
    if (checkNameValid(artist) == ERROR_INVALID_INPUTS)
        return ERROR_INVALID_INPUTS;
    if (trackLengthInSec <= 0)
        return ERROR_INVALID_INPUTS;

    Track new_track = malloc(sizeof (struct track));
   
    // store the info into a new track
    strcpy(new_track->title, title);
    strcpy(new_track->artist, artist);

    struct trackLength length;
    length.minutes = trackLengthInSec/60;
    length.seconds = trackLengthInSec%60;
    new_track->length = length;
    // printf("%d %d\n", length.minutes, length.seconds);

    Track curr_track = selected_list->tracks;
    if (position == 0) {
        new_track->next = curr_track;
        selected_list->tracks = new_track;
        selected_list->num_track++;
    } else {
        int i = 0;
        int flag = UNFLAGED;
        while (curr_track != NULL && flag == UNFLAGED) {
            if (i + 1 == position) {
                Track next_track = curr_track->next;
                curr_track->next = new_track;
                new_track->next = next_track;
                selected_list->num_track++;
                flag = FLAGED;
            }
            curr_track = curr_track->next;
            i++;
        }
    }

    return SUCCESS;
}

// Calculate the total length of the selected Playlist in minutes and seconds.
void playlist_length(Library library, int *playlistMinutes, int *playlistSeconds) {
    
    Playlist selected_list = getSelected(library);
    if (selected_list != NULL) { 
        int minutes = 0;
        int seconds = 0;

        Track curr_track = selected_list->tracks;

        while (curr_track != NULL) {
            minutes += curr_track->length.minutes;
            seconds += curr_track->length.seconds;
            if (seconds >= 60) {
                minutes += seconds / 60;
                seconds = seconds % 60;
            }
            curr_track = curr_track->next;
        }
        *playlistMinutes = minutes;
        *playlistSeconds = seconds;
    } else {
        *playlistMinutes = ERROR_INVALID_INPUTS;
        *playlistSeconds = ERROR_INVALID_INPUTS;
    }


}


/*********
> STAGE 3
*********/

static void free_playlist(Playlist pl) {
    Track curr = pl->tracks;
    Track prev = NULL;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(pl);
}

// Delete the first instance of the given track in the selected Playlist
// of the Library.
void delete_track(Library library, char track[MAX_LEN]) {
    Playlist selected = getSelected(library);
    if (selected != NULL) {
        Track curr = selected->tracks;
        int flag = UNFLAGED;
    
        if (strcmp(curr->title, track) == 0) {
            selected->tracks = curr->next;
            curr->next = NULL;
            free(track);
        } else {
            Track prev = NULL;
            while (curr != NULL && flag == UNFLAGED) {
                if (strcmp(curr->title, track) == 0) {
                    flag = FLAGED;
                    prev->next = curr->next;
                    curr->next = NULL;
                    free(track);
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
}

// Delete the selected Playlist and select the next Playlist in the Library.
void delete_playlist(Library library) {
    Playlist curr = library->head;
    if (curr->selected == SELECTED) {
        library->head = curr->next;
        if (curr->next == NULL) {
            library->head->selected = SELECTED;
        } else {
            curr->next->selected = SELECTED;
        }
        curr->next = NULL;
        free_playlist(curr);
    } else {
        Playlist prev = NULL;
        int flag = UNFLAGED;
        while (curr != NULL && flag == UNFLAGED) {
            if (curr->selected == SELECTED) {
                flag = FLAGED;
                prev->next = curr->next;
                if (curr->next == NULL) {
                    library->head->selected = SELECTED;
                } else {
                    curr->next->selected = SELECTED;
                }
                curr->next = NULL;
                free_playlist(curr);
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

// Delete an entire Library and its associated Playlists and Tracks.
void delete_library(Library library) {
    Playlist curr = library->head;
    Playlist prev = NULL;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free_playlist(prev);
    }
    free(library);
}


/*********
> STAGE 4
*********/

// Cut the given track in selected Playlist and paste it into the given 
// destination Playlist.
int cut_and_paste_track(Library library, char trackTitle[MAX_LEN], 
    char destPlaylist[MAX_LEN]) {
    return SUCCESS;
}

// Print out all Tracks with artists that have the same Soundex Encoding 
// as the given artist.
void soundex_search(Library library, char artist[MAX_LEN]) {

}


/*********
> STAGE 5
*********/

// Move all Tracks matching the Soundex encoding of the given artist 
// to a new Playlist.
int add_filtered_playlist(Library library, char artist[MAX_LEN]) {
    return SUCCESS;
}

// Reorder the selected Playlist in the given order specified by the order array.
void reorder_playlist(Library library, int order[MAX_LEN], int length) {

}


/*****************
> Helper Functions
*****************/

static void print_playlist(int number, char playlistName[MAX_LEN]) {
    printf("[ ] %d. %s\n", number, playlistName);
}

static void print_selected_playlist(int number, char playlistName[MAX_LEN]) {
    printf("[*] %d. %s\n", number, playlistName);
}

static void print_track(char title[MAX_LEN], char artist[MAX_LEN], int minutes, int seconds) {
    printf("       - %-32s    %-24s    %02d:%02d\n", title, artist, 
        minutes, seconds);
}
