#include "SortingMethod.h"

class SortByLength::Impl {
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

SortByLength::SortByLength() : pImpl(std::make_unique<Impl>()) {}

SortByLength::~SortByLength() = default;

void SortByLength::sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist) {
   SortByLength::Impl::TreeNode *root = new SortByLength::Impl::TreeNode(playlist.front());
   for(auto it = ++playlist.begin(); it < playlist.end(); ++it) {
      pImpl->insert(root, *it);
   }
   std::vector<std::shared_ptr<Song>> sortedPlaylist;
   pImpl->order(root, sortedPlaylist);
   pImpl->destroyTree(root);

   playlist = sortedPlaylist;
}

std::unique_ptr<SortingMethod> SortByLength::clone() const {
   return std::make_unique<SortByLength>();
}