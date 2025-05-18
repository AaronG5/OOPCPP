// Demonstration of SongPlaylist and sorting method polymorphism

#include "Song.h" 
#include "SongPlaylist.h"
#include "SortingMethod.h"
#include <iostream>

using namespace std;

int main() {
   try {
      cout << "Demonstration of SongPlaylist and sorting method polymorphism\n" << endl;
      cout <<  "User wants to make a new playlist and add songs to it.\n" << endl;
      SongPlaylist *jazz = new SongPlaylist();
   
      jazz->addSong(make_shared<Song>("Tenderly", "Chet Baker", 6, 38));
      jazz->addSong(make_shared<Song>("Look To The Sky", "Antonio Carlos Jobim", 2, 20));
      jazz->addSong(make_shared<Song>("Prelude In E Minor", "Gerry Mulligan Sextet", 4, 17));
      jazz->addSong(make_shared<Song>("Fiasco", "Gus Viseur", 2, 58));
   
      cout << "User checks his playlist by displaying every song." << endl;
      cout << jazz->getPlaylistInfo() << endl;
   
      cout << "User creates a new playlist and adds a songs from the previous playlist.\n" << endl;
      SongPlaylist *brazilianJazz = new SongPlaylist();
      jazz->addSongToOtherPlaylist("Look To The Sky", *brazilianJazz);
      brazilianJazz->addSong(make_shared<Song>("Flor Do Brazil", "Jean Bonal", 2, 12));
   
      cout << "User is tired of one of the songs, so he removes it from the playlist.\n" << endl;
      jazz->removeSong("Fiasco");
   
      cout << "User is interested in the name of the artist of a specific song, so he checks the song info." << endl;
      cout << jazz->getSong("Prelude In E Minor")->getSongInfo() << endl;
   
      cout << "\nUser adds a couple more songs to his playlist and wants to sort it by the length of the songs.\n" << endl;
      jazz->addSong(make_shared<Song>("When Sunny Gets Blue", "McCoy Tyner", 4, 42));
      jazz->addSong(make_shared<Song>("It Never Entered My Mind", "Miles Davis", 4, 3));
      jazz->setSortMethod(make_unique<SortByLength>()); // POLYMORPHISM
      jazz->sortPlaylist(); // POLYMORPHISM
      jazz->getPlaylistInfo();
   
      cout << "User thinks that the playlist would be nicer if it were sorted by song title.\n" << endl;
      jazz->setSortMethod(make_unique<SortByTitle>()); // POLYMORPHISM
      jazz->sortPlaylist(); // POLYMORPHISM
      jazz->getPlaylistInfo();
   
      cout << "User gets tired of his brazilian jazz playlist, so he deletes it.\n" << endl;
      delete brazilianJazz;
      
      cout << "User tries to delete a song from his playlist even though its already deleted.\n" << endl;
      jazz->removeSong("Fiasco");
   } 
   catch(out_of_range &e) { cout << e.what() << endl; } 
   catch(invalid_argument &e) { cout << e.what() << endl; } 
   catch(...) { cout << "Unknown exception caught!" << endl; }

   cout << "\nEnd of demonstration" << endl;

   return 0;
}