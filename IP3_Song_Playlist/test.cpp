// Required derived class to implement: SortByArtist
// It is required to implement some kind of custom sorting algorithm instead of just using std::sort().

#include "SongPlaylist.h"
#include "SortingMethod.h"
#include <cassert>
#include <iostream>

using namespace std;

void addSongs(SongPlaylist *&playlist) {
      playlist->addSong(make_shared<Song>("Holding The Moth", "Underworld", 5, 29));
      playlist->addSong(make_shared<Song>("Pripjaty Pandemonium", "BANDEE", 6, 31));
      playlist->addSong(make_shared<Song>("XXX", "6EJOU", 6, 37));
      playlist->addSong(make_shared<Song>("Beautiful Burnout", "Underworld", 8, 9));
      playlist->addSong(make_shared<Song>("The Orange Theme - Original Version", "Cygnus X", 6, 31));
      playlist->addSong(make_shared<Song>("AC130", "Luciid", 356));
}

void getAndCompareTest() {
   SongPlaylist *playlist = new SongPlaylist();
   try {
      // addSong test
      addSongs(playlist);

      // getSong, operator[] and Song method operator== test
      assert(playlist->getSong("Holding The Moth") == (*playlist)[0]);
      assert(playlist->getSong("Pripjaty Pandemonium") == (*playlist)[1]);
      assert(playlist->getSong("XXX") == (*playlist)[2]);
      assert(playlist->getSong("Beautiful Burnout") == (*playlist)[3]);
      assert(playlist->getSong("The Orange Theme - Original Version") == (*playlist)[4]);
      assert(playlist->getSong("AC130") == (*playlist)[5]);

      // Individual object field comparison and get method test
      assert(playlist->getSong("AC130")->getUniqueId() == (*playlist)[5]->getUniqueId()); 
      assert(playlist->getSong("AC130")->getTitle() == (*playlist)[5]->getTitle());
      assert(playlist->getSong("AC130")->getArtist() == (*playlist)[5]->getArtist());
      assert(playlist->getSong("AC130")->getLength() == (*playlist)[5]->getLength());

   } catch(...) { cout << "Exception caught!" << endl; }
   
   delete playlist;
   cout << "Get method and comparison tests passed." << endl;
}

void exceptionTest() {
   cout << "Exception test start.\n" << endl; 
   SongPlaylist *playlist = new SongPlaylist();
   int exceptionCounter = 0;
   
   playlist->addSong(make_shared<Song>("Tomorrow", "Tyler, The Creator", 3, 2));
   assert(playlist->getSong("Tomorrow"));
   
   playlist->removeSong("Tomorrow");
   try { playlist->getSong("Tomorrow"); } 
   catch(invalid_argument &e) { 
      cout << e.what() << endl; 
      ++exceptionCounter;
   }
   
   try { playlist->getSong("November"); }
   catch(invalid_argument &e) {
      cout << e.what() << endl; 
      ++exceptionCounter;
   }

   try { playlist->removeSong("Sireneh"); }
   catch(invalid_argument &e) { 
      cout << e.what() << endl; 
      ++exceptionCounter;
   }
   
   shared_ptr<Song> songNull = nullptr;
   try { playlist->addSong(songNull); }
   catch(invalid_argument &e) { 
      cout << e.what() << endl; 
      ++exceptionCounter;
   }

   try { (*playlist)[0]; }
   catch(out_of_range &e) {
      cout << e.what() << endl; 
      ++exceptionCounter;
   }

   delete playlist;
   if(exceptionCounter == 5) { cout << "\nException tests passed." << endl; }
}

void multiplePlaylistTest() {
   SongPlaylist *playlist1 = new SongPlaylist();
   SongPlaylist *playlist2 = new SongPlaylist();
   try {
      playlist1->addSong(make_shared<Song>("XXX", "6EJOU", 6, 37));
      playlist1->addSong(make_shared<Song>("Obscured by Clouds", "Pink Floyd", 3, 4));

      playlist1->addSongToOtherPlaylist("XXX", *playlist2);
      assert(playlist1->getSong("XXX") == playlist2->getSong("XXX"));

      playlist2->addSong((*playlist1)[1]);
      assert((*playlist1)[1] == playlist2->getSong("Obscured by Clouds"));

   } catch(...) { cout << "Exception caught!" << endl; }

   delete playlist1;
   delete playlist2;
   cout << "Multiple playlist test passed." << endl;
}

void sortByLengthTest() {
   try {
      SongPlaylist *playlist1 = new SongPlaylist();
      addSongs(playlist1);
      SongPlaylist *playlist2 = new SongPlaylist(*playlist1);

      playlist1->setSortMethod(make_unique<SortByLength>());
      playlist1->sortPlaylist();

      assert(!(playlist1->getPlaylist() == playlist2->getPlaylist()));
      assert((*playlist1)[0]->getTitle() == "Holding The Moth");
      assert((*playlist1)[1]->getTitle() == "AC130");
      assert(
         ((*playlist1)[2]->getTitle() == "Pripjaty Pandemonium") || 
         ((*playlist1)[2]->getTitle() == "The Orange Theme - Original Version")
      );
      assert(
         ((*playlist1)[3]->getTitle() == "Pripjaty Pandemonium") || 
         ((*playlist1)[3]->getTitle() == "The Orange Theme - Original Version")
      );
      assert((*playlist1)[4]->getTitle() == "XXX");
      assert((*playlist1)[5]->getTitle() == "Beautiful Burnout");

      playlist1->addSong(make_shared<Song>("Gummo Hardrive", "Liquid Earth", 6, 33));
      assert((*playlist1)[4]->getTitle() == "Gummo Hardrive");
      assert((*playlist1)[5]->getTitle() == "XXX");
      assert((*playlist1)[6]->getTitle() == "Beautiful Burnout");

   } catch(...) { cout << "Exception caught!" << endl; }

   cout << "Sort by length test passed" << endl;
}

void sortByTitleTest() {
   try {
      SongPlaylist *playlist1 = new SongPlaylist();
      addSongs(playlist1);
      SongPlaylist *playlist2 = new SongPlaylist(*playlist1);

      playlist1->setSortMethod(make_unique<SortByTitle>());
      playlist1->sortPlaylist();

      assert(!(playlist1->getPlaylist() == playlist2->getPlaylist()));
      assert((*playlist1)[0]->getTitle() == "AC130");
      assert((*playlist1)[1]->getTitle() == "Beautiful Burnout");
      assert((*playlist1)[2]->getTitle() == "Holding The Moth");
      assert((*playlist1)[3]->getTitle() == "Pripjaty Pandemonium"); 
      assert((*playlist1)[4]->getTitle() == "The Orange Theme - Original Version");
      assert((*playlist1)[5]->getTitle() == "XXX");

      playlist1->addSong(make_shared<Song>("Gummo Hardrive", "Liquid Earth", 6, 33));
      assert((*playlist1)[1]->getTitle() == "Beautiful Burnout");
      assert((*playlist1)[2]->getTitle() == "Gummo Hardrive");
      assert((*playlist1)[3]->getTitle() == "Holding The Moth");
      assert((*playlist1)[6]->getTitle() == "XXX");

   } catch(...) { cout << "Exception caught!" << endl; }
   cout << "Sort by title test passed" << endl;
}

void sortByArtistTest() {
   try {
      SongPlaylist *playlist1 = new SongPlaylist();
      addSongs(playlist1);
      SongPlaylist *playlist2 = new SongPlaylist(*playlist1);

      playlist1->setSortMethod(make_unique<SortByArtist>());
      playlist1->sortPlaylist();

      assert(!(playlist1->getPlaylist() == playlist2->getPlaylist()));
      assert((*playlist1)[0]->getTitle() == "XXX");
      assert((*playlist1)[1]->getTitle() == "Pripjaty Pandemonium"); 
      assert((*playlist1)[2]->getTitle() == "The Orange Theme - Original Version");
      assert((*playlist1)[3]->getTitle() == "AC130");
      assert(
         ((*playlist1)[4]->getTitle() == "Beautiful Burnout") || 
         ((*playlist1)[4]->getTitle() == "Holding The Moth")
      );
      assert(
         ((*playlist1)[5]->getTitle() == "Beautiful Burnout") || 
         ((*playlist1)[5]->getTitle() == "Holding The Moth")
      );

      playlist1->addSong(make_shared<Song>("Gummo Hardrive", "Liquid Earth", 6, 33));
      assert((*playlist1)[2]->getTitle() == "The Orange Theme - Original Version");
      assert((*playlist1)[3]->getTitle() == "Gummo Hardrive");
      assert((*playlist1)[4]->getTitle() == "AC130");

   } catch(...) { cout << "Exception caught!" << endl; }
   cout << "Sort by artist test passed" << endl;
}

int main() {

   getAndCompareTest();
   exceptionTest();
   multiplePlaylistTest();
   sortByLengthTest();
   sortByTitleTest();
   // sortByArtistTest();
   cout << "All tests passed!" << endl;
   
   return 0;
}