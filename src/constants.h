#pragma once

constexpr size_t IMAGE_WIDTH = 2000;
constexpr size_t IMAGE_HEIGHT = 1000;
constexpr size_t SAMPLES_PER_PIXEL = 100;
constexpr int MAX_DEPTH = 50;

constexpr auto ASPECT_RATIO = static_cast<double>(IMAGE_WIDTH) / IMAGE_HEIGHT;
