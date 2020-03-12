#ifndef ROW_H_
#define ROW_H_
#include <cstdint>

#define kColumnUrlSize 255
#define kColumnTitleSize 255

// void SerializeRow(Row* source, void* destination);
// void DeserializeRow(void* source, Row* destination);

class Row{
  public:
    std::uint32_t id;
    char url[kColumnUrlSize+1];
    char title[kColumnTitleSize+1];

  private:
    const static std::uint32_t kIdSize = sizeof(id);
    const static std::uint32_t kUrlSize = sizeof(url);
    const static std::uint32_t kTitleSize = sizeof(title);

    const static std::uint32_t kIdOffset = 0;
    const static std::uint32_t kUrlOffset = kIdOffset + kIdSize;
    const static std::uint32_t kTitleOffset = kUrlOffset + kUrlSize;

  public:
    const static std::uint32_t kRowSize = kIdSize + kUrlSize + kTitleSize;

    void Serialize(void* destination);
    void Deserialize(void* source);
    void Print();
};

#endif // ROW_H_