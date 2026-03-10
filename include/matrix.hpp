#pragma once

#include <array>
#include <cstddef>

template <typename T, size_t Y, size_t X>
class FlatMatrix {
  private:
    std::array<T, Y * X> flat_matrix_;

  public:
    constexpr FlatMatrix() = default;

    constexpr T& operator[](size_t y, size_t x) noexcept { return flat_matrix_[y * X + x]; }
    constexpr const T& operator[](size_t y, size_t x) const noexcept { return flat_matrix_[y * X + x]; }

    constexpr size_t height() const noexcept { return Y; }
    constexpr size_t width() const noexcept { return X; }
};
