#ifndef SUM_SEGTREE_HPP
#define SUM_SEGTREE_HPP

#include <utility>
#include <vector>

namespace ALGO {

/* Segment tree for summ queries */
template <typename T>
class sum_segtree {

  /* Original size of actual data */
  size_t original_size_;

  /* Size of data round up to the nearest power of 2 */
  size_t data_size_;

  /* Size of data array for the tree itself */
  size_t tree_size_;

  /* Tree's data */
  std::vector<T> tree_;

public:

  sum_segtree(const std::vector<T>& data):
  original_size_(data.size()),
  data_size_(compute_data_size(original_size_)),
  tree_size_(data_size_ * 4),
  tree_(tree_size_, 0U) {

    build(data, 1, 0, data_size_ - 1);
  }

  virtual ~sum_segtree() {}

  T query(size_t left, size_t right) const {
    return query_recursive(1, 0, data_size_ - 1, left, right);
  }

  void update(size_t index, const T& value) {
    update_recursive(1, 0, data_size_ - 1, index, value);
  }

private:

  static size_t compute_data_size(size_t v) {

    /* Round up to the nearest power of 2 */
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    return v;
  }

  void build(const std::vector<T>& data, 
    size_t cur_idx, size_t l_idx, size_t r_idx);

  T query_recursive(size_t cur_idx, size_t l_idx, size_t r_idx, 
    size_t ql_idx, size_t qr_idx) const ;

  void update_recursive(size_t cur_idx, size_t l_idx, size_t r_idx, 
    size_t index, const T& value);
};

template <typename T>
void sum_segtree<T>::build(const std::vector<T>& data, 
  size_t cur_idx, size_t l_idx, size_t r_idx) {

  if (l_idx >= original_size_) {
    return;
  }

  if (l_idx == r_idx) {
    tree_[cur_idx] = data[l_idx];

  } else {

    size_t m_idx = (l_idx + r_idx) / 2;

    size_t l_child_idx = cur_idx * 2;
    size_t r_child_idx = cur_idx * 2 + 1;

    build(data, l_child_idx, l_idx, m_idx);
    build(data, r_child_idx, m_idx + 1, r_idx);

    tree_[cur_idx] = tree_[l_child_idx] + tree_[r_child_idx];
  }
}


template <typename T>
T sum_segtree<T>::query_recursive(size_t cur_idx, size_t l_idx, size_t r_idx, 
  size_t ql_idx, size_t qr_idx) const {

  if (l_idx == ql_idx && r_idx == qr_idx) {

    return tree_[cur_idx];
  }

  size_t m_idx = (l_idx + r_idx) / 2;
  
  size_t l_child_idx = cur_idx * 2;
  size_t r_child_idx = cur_idx * 2 + 1;
  
  T res = 0;

  if (ql_idx <= std::min(qr_idx, m_idx)) {
    res += query_recursive(l_child_idx, l_idx, m_idx, ql_idx, std::min(qr_idx, m_idx));
  }

  if (std::max(m_idx + 1, ql_idx) <= qr_idx) {
    res += query_recursive(r_child_idx, m_idx + 1, r_idx, std::max(m_idx + 1, ql_idx), qr_idx);
  }

  return res;
}

template <typename T>
void sum_segtree<T>::update_recursive(size_t cur_idx, size_t l_idx, size_t r_idx, 
  size_t index, const T& value) {

  if (l_idx == r_idx) {
    tree_[cur_idx] = value;
    return;
  }

  size_t m_idx = (l_idx + r_idx) / 2;
  
  size_t l_child_idx = cur_idx * 2;
  size_t r_child_idx = cur_idx * 2 + 1;

  if (index <= m_idx) {
    update_recursive(l_child_idx, l_idx, m_idx, index, value);

  } else {
    update_recursive(r_child_idx, m_idx + 1, r_idx, index, value);
  }

  tree_[cur_idx] = tree_[l_child_idx] + tree_[r_child_idx];
}

}; // namespace ALGO

#endif // SUM_SEGTREE_HPP
