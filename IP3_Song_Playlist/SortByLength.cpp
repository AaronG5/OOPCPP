#include "SortByLength.h"

class SortByLength::Algorithm {
   private:
   struct TreeNode {
      std::shared_ptr<Song> song;
      TreeNode *left;
      TreeNode *right;
      TreeNode(std::shared_ptr<Song> song) : song(song), left(nullptr), right(nullptr) {};
   };

   void insert(TreeNode *&root, const std::shared_ptr<Song>& song) {
      if(!root) { root = new TreeNode(song); }
      else if(song->getLength() < root->song->getLength()) { insert(root->left, song); }
      else { insert(root->right, song); }
   }

   void order(TreeNode *root, std::vector<std::shared_ptr<Song>>& sortedPlaylist) {
      if(!root) { return; }
      order(root->left, sortedPlaylist);
      sortedPlaylist.push_back(root->song);
      order(root->right, sortedPlaylist);
   }

   void destroyTree(TreeNode *root) {
      if(!root) { return; }
      destroyTree(root->left);
      destroyTree(root->right);
      delete root;
   }

   friend SortByLength;
};

void SortByLength::sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist) {
   SortByLength::Algorithm::TreeNode *root = new SortByLength::Algorithm::TreeNode(playlist.front());
   for(auto it = ++playlist.begin(); it < playlist.end(); ++it) {
      pImpl->insert(root, *it);
   }
   std::vector<std::shared_ptr<Song>> sortedPlaylist;
   pImpl->order(root, sortedPlaylist);
   pImpl->destroyTree(root);

   playlist = sortedPlaylist;
}