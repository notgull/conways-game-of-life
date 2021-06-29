// MIT License

#include <cstdint>
#include <memory>

class Cell {
  public:
    uint64_t x;
    uint64_t y;
    Cell(uint64_t cx, uint64_t cx) : x(cx), y(cy) {}
};

class Node {
  private:
    Cell cell;
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};
