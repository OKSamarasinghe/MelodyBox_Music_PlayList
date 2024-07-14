#include <iostream>
#include <algorithm> // Include for all-of function
#include <limits>    // Include for numeric-limits
#include <sstream>
#include <cstring>

// Class representing a song
class Song {
private:
    char* name;
    char* artist;
    int duration; // in seconds

public:
    // Constructor
    Song(const char* name, const char* artist, int duration) : duration(duration) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->artist = new char[strlen(artist) + 1];
        strcpy(this->artist, artist);
    }

    // Destructor
    ~Song() {
        delete[] name;
        delete[] artist;
    }

    // Getter methods
    const char* getName() const {
        return name;
    }

    const char* getArtist() const {
        return artist;
    }

    int getDuration() const {
        return duration;
    }
};

// Class representing a node in a linked list
class Node {
public:
    Song* song;
    Node* next;

    // Constructor
    Node(Song* song) : song(song), next(nullptr) {}

    // Destructor
    ~Node() {
        delete song;
    }
};

// Class representing a linked list of songs
class LinkedList {
public:
    Node* head;

    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Method to add a song to the playlist
    void addSong(Song* song) {
        Node* newNode = new Node(song);
        newNode->next = head;
        head = newNode;
    }

    // Method to delete a song from the playlist
    void deleteSong(const char* songName) {
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr && strcmp(current->song->getName(), songName) != 0) {
            prev = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            std::cout << "Song '" << songName << "' has been deleted." << std::endl;
        } else {
            std::cout << "Song '" << songName << "' not found." << std::endl;
        }
    }

    // Method to display the playlist
    void displayPlaylist() {
        Node* current = head;
        std::cout << "Playlist:" << std::endl;
        while (current != nullptr) {
            std::cout << "- " << current->song->getName() << " by " << current->song->getArtist() << " (" << current->song->getDuration() << "s)" << std::endl;
            current = current->next;
        }
    }

    // Method to sort the playlist by song name
    void sortPlaylist() {
        // Bubble sort (simple sorting algorithm)
        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current != nullptr && current->next != nullptr) {
                if (strcmp(current->song->getName(), current->next->song->getName()) > 0) {
                    // Swap songs
                    Song* temp = current->song;
                    current->song = current->next->song;
                    current->next->song = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        std::cout << "Playlist sorted by song name." << std::endl;
    }
};

// Function to play a song from the playlist
void playSong(const char* songName, LinkedList& playlist) {
    Node* current = playlist.head;
    while (current != nullptr) {
        if (strcmp(current->song->getName(), songName) == 0) {
            std::cout << "Playing: " << current->song->getName() << " by " << current->song->getArtist() << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "Song '" << songName << "' not found." << std::endl;
}

// Main function
int main() {
    LinkedList playlist;

    // Add sample songs
    /*playlist.addSong(new Song("Song1", "Artist1", 200));
    playlist.addSong(new Song("Song2", "Artist2", 180));
    playlist.addSong(new Song("Song3", "Artist3", 220));
    playlist.addSong(new Song("Song4", "Artist4", 240));
    playlist.addSong(new Song("Song5", "Artist5", 210));*/

    std::string choice;
    std::string name, artist;
    int duration;
    std::string songName;
    while (true) {
        std::cout << "\n----------------------------\nMelody Box Music Play List\n\nMenu:\n1. Add Song\n2. Delete Song\n3. Display Playlist\n4. Sort Playlist\n5. Play Song\n6. Exit\nPlease type -99 to return to the menu\n\nEnter choice: ";
        std::cin >> choice;

        // Input validation
        if (!std::all_of(choice.begin(), choice.end(), ::isdigit)) {
            std::cout << "!! Please Enter Numbers Only !!" << std::endl;
            // Clear the input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == "-99") {
            break; // Exit the loop and terminate the program
        }

        int choiceInt = std::stoi(choice); // Convert string choice to integer

        // Switch case for different menu options
        switch (choiceInt) {
            case 1:
                {
                    // Add a new song
                    std::cout << "Enter song name: ";
                    std::cin >> name;
                    if (name == "-99") {
                        break; // Exit the loop and terminate the program
                    }
                    std::cout << "Enter artist name: ";
                    std::cin >> artist;
                    if (artist == "-99") {
                        break; // Exit the loop and terminate the program
                    }
                    std::cout << "Enter duration (in seconds): ";
                    std::cin >> duration;
                    if (duration == -99) {
                        break; // Exit the loop and terminate the program
                    }
                    playlist.addSong(new Song(name.c_str(), artist.c_str(), duration));
                    break;
                }
            case 2:
                // Delete a song
                std::cout << "Enter song name to delete: ";
                std::cin >> songName;
                if (songName == "-99") {
                    break; // Exit the loop and terminate the program
                }
                playlist.deleteSong(songName.c_str());
                break;
            case 3:
                // Display the playlist
                playlist.displayPlaylist();
                break;
            case 4:
                // Sort the playlist
                playlist.sortPlaylist();
                break;
            case 5:
                // Play a song
                {
                    std::cout << "Enter song name to play: ";
                    std::cin >> songName;
                    if (songName == "-99") {
                        break; // Exit the loop and terminate the program
                    }
                    playSong(songName.c_str(), playlist);
                    break;
                }
            case 6:
                // Exit the program
                std::cout << "Exiting program." << std::endl;
                return 0;
            default:
                // Invalid choice
                std::cout << "Invalid choice. Please enter a number between 1 and 6." << std::endl;
                break;
        }
    }

    return 0;
}
