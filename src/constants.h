#pragma once

constexpr size_t IMAGE_WIDTH = 1600;
constexpr size_t IMAGE_HEIGHT = 800;
constexpr size_t SAMPLES_PER_PIXEL = 100;
constexpr int MAX_DEPTH = 50;

constexpr auto ASPECT_RATIO = static_cast<double>(IMAGE_WIDTH) / IMAGE_HEIGHT;
