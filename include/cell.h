// MIT License

#include <cstdint>
#include <memory>

class Cell {
  public:
    int64_t x;
    int64_t y;
    Cell(int64_t cx, int64_t cy); 
};

class Node {
  private:
    Cell cell;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};
