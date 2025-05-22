#include "SortingAlgorithm.h"

class TreeSort::Impl {
   private:
   struct TreeNode {
      std::shared_ptr<Song> song;
      TreeNode *left;
      TreeNode *right;
      TreeNode(std::shared_ptr<Song> song) : song(song), left(nullptr), right(nullptr) {};
   };

   void insert(TreeNode *&root, const std::shared_ptr<Song>& song, const std::unique_ptr<CompareStrategy>& comparator) {
      if(!root) { root = new TreeNode(song); }
      else if(comparator->compare(song, root->song)) { insert(root->left, song, comparator); }
      else { insert(root->right, song, comparator); }
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

   friend TreeSort;
};

TreeSort::TreeSort() : pImpl(std::make_unique<Impl>()) {}

TreeSort::~TreeSort() = default;

void TreeSort::sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist, const std::unique_ptr<CompareStrategy>& comparator) {
   TreeSort::Impl::TreeNode *root = new TreeSort::Impl::TreeNode(playlist.front());
   for(auto it = ++playlist.begin(); it < playlist.end(); ++it) {
      pImpl->insert(root, *it, comparator);
   }
   std::vector<std::shared_ptr<Song>> sortedPlaylist;
   pImpl->order(root, sortedPlaylist);
   pImpl->destroyTree(root);

   playlist = sortedPlaylist;
}

std::unique_ptr<SortingAlgorithm> TreeSort::clone() const {
   return std::make_unique<TreeSort>();
}