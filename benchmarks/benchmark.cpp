#include "benchmark.h"
#include "../archiver_main/archiver_main.h"
#include <iostream>
#include <ctime>

Benchmark::Benchmark() {

}

void Benchmark::RunBenchmark() {
    TextBenchmark();
    AudioBenchmark();
    VideoBenchmark();
}

void Benchmark::TextBenchmark() {
    std::cout << "Text:" << std::endl;
    std::fstream file("../benchmarks/text.txt");
    file.seekg(0, std::ios::end);
    size_t size_in_bytes = file.tellg();
    file.close();
    Archiver archiver;
    int64_t start_time = clock();
    archiver.Archive("../benchmarks/archive_text.txt", {"../benchmarks/text.txt"});
    int64_t end_time = clock();
    double time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double compress_speed = (static_cast<double>(size_in_bytes) / time) / 1024 / 1024;
    std::cout << "Compress speed: " << compress_speed << " mb/s" << std::endl;
    file.open("../benchmarks/archive_text.txt");
    file.seekg(0, std::ios::end);
    size_t archived_size_in_bytes = file.tellg();
    file.close();
    std::cout << "Compress ratio: " << static_cast<double>(size_in_bytes) / static_cast<double>(archived_size_in_bytes) << std::endl;
    start_time = clock();
    archiver.Dearchive("../benchmarks/archive_text.txt");
    end_time = clock();
    time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double decompress_speed = (static_cast<double>(size_in_bytes) / time) / 1024 / 1024;
    std::cout << "Decompress speed: " << decompress_speed << " mb/s" << std::endl;
    remove("../benchmarks/archive_text.txt");
}

void Benchmark::AudioBenchmark() {
    std::cout << "Audio:" << std::endl;
    std::fstream file("../benchmarks/audio.mp3");
    file.seekg(0, std::ios::end);
    size_t size_in_bytes = file.tellg();
    file.close();
    Archiver archiver;
    int64_t start_time = clock();
    archiver.Archive("../benchmarks/archive_audio.txt", {"../benchmarks/audio.mp3"});
    int64_t end_time = clock();
    double time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double compress_speed = (static_cast<double>(size_in_bytes) / time) / 1024 / 1024;
    std::cout << "Compress speed: " << compress_speed << " mb/s" << std::endl;
    file.open("../benchmarks/archive_audio.txt");
    file.seekg(0, std::ios::end);
    size_t archived_size_in_bytes = file.tellg();
    file.close();
    std::cout << "Compress ratio: " << static_cast<double>(size_in_bytes) / static_cast<double>(archived_size_in_bytes) << std::endl;
    start_time = clock();
    archiver.Dearchive("../benchmarks/archive_audio.txt");
    end_time = clock();
    time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double decompress_speed = (static_cast<double>(size_in_bytes) / time) / 1024 / 1024;
    std::cout << "Decompress speed: " << decompress_speed << " mb/s" << std::endl;
    remove("../benchmarks/archive_audio.txt");
}

void Benchmark::VideoBenchmark() {
  std::cout << "Video:" << std::endl;
    std::fstream file("../benchmarks/video.mp4");
    file.seekg(0, std::ios::end);
    size_t size_in_bytes = file.tellg();
    file.close();
    Archiver archiver;
    int64_t start_time = clock();
    archiver.Archive("../benchmarks/archive_video.txt", {"../benchmarks/video.mp4"});
    int64_t end_time = clock();
    double time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double compress_speed = (static_cast<double>(size_in_bytes) / time) / 1024 / 1024;
    std::cout << "Compress speed: " << compress_speed << " mb/s" << std::endl;
    file.open("../benchmarks/archive_video.txt");
    file.seekg(0, std::ios::end);
    size_t archived_size_in_bytes = file.tellg();
    file.close();
    std::cout << "Compress ratio: " << static_cast<double>(size_in_bytes) / static_cast<double>(archived_size_in_bytes) << std::endl;
    start_time = clock();
    archiver.Dearchive("../benchmarks/archive_video.txt");
    end_time = clock();
    time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double decompress_speed = (static_cast<double>(size_in_bytes) / time) / 1024 / 1024;
    std::cout << "Decompress speed: " << decompress_speed << " mb/s" << std::endl;
    remove("../benchmarks/archive_video.txt");
}
