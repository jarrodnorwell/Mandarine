#include "config.h"
#include "sound/sound.h"
#include "system.h"
#include "tools.h"
#include "mainwindow.h"

#include <deque>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <QDebug>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

bool fileExists(const std::string &path)
{
    return std::filesystem::exists(path);
}

std::vector<uint8_t> getFileContents(const std::string &path)
{
    std::vector<uint8_t> contents;

    FILE *f = fopen(path.c_str(), "rb");
    if (!f)
        return contents;

    fseek(f, 0, SEEK_END);
    int filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    contents.resize(filesize);
    fread(&contents[0], 1, filesize, f);

    fclose(f);
    return contents;
}

bool putFileContents(const std::string &name, const std::vector<unsigned char> &contents)
{
    FILE *f = fopen(name.c_str(), "wb");
    if (!f)
        return false;

    fwrite(&contents[0], 1, contents.size(), f);

    fclose(f);

    return true;
}
bool writeToDisc(const std::string &name, const std::vector<uint8_t> &contents) { return putFileContents(name, contents); };

bool putFileContents(const std::string &path, const std::string contents)
{
    FILE *f = fopen(path.c_str(), "wb");
    if (!f)
        return false;

    fwrite(&contents[0], 1, contents.size(), f);

    fclose(f);

    return true;
}

std::string getFileContentsAsString(const std::string &path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Could not open file");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

size_t getFileSize(const std::string &path)
{
    return std::filesystem::file_size(path);
}

double limitFramerate(bool framelimiter, bool ntsc) {
    static double timeToSkip = 0;
    static double counterFrequency = (double)SDL_GetPerformanceFrequency();
    static double startTime = SDL_GetPerformanceCounter() / counterFrequency;
    static double fpsTime = 0.0;
    static double fps = 0;
    static int deltaFrames = 0;

    double currentTime = SDL_GetPerformanceCounter() / counterFrequency;
    double deltaTime = currentTime - startTime;

    double frameTime = ntsc ? (1.0 / timing::NTSC_FRAMERATE) : (1.0 / timing::PAL_FRAMERATE);

    if (framelimiter && deltaTime < frameTime) {
        // If deltaTime was shorter than frameTime - spin
        if (deltaTime < frameTime - timeToSkip) {
            while (deltaTime < frameTime - timeToSkip) {  // calculate real difference
                SDL_Delay(1);

                currentTime = SDL_GetPerformanceCounter() / counterFrequency;
                deltaTime = currentTime - startTime;
            }
            timeToSkip -= (frameTime - deltaTime);
            if (timeToSkip < 0.0) timeToSkip = 0.0;
        }
        else {  // Else - accumulate
            timeToSkip += deltaTime - frameTime;
        }
    }

    startTime = currentTime;
    fpsTime += deltaTime;
    deltaFrames++;

    if (fpsTime > 0.25f) {
        fps = (double)deltaFrames / fpsTime;
        deltaFrames = 0;
        fpsTime = 0.0;
    }

    return fps;
}

int main(int argc, char *argv[]) {
    std::jthread([&](std::stop_token token) {
        using namespace std::chrono;

        SDL_SetMainReady();
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_CreateWindowAndRenderer("Mandarine", gpu::VRAM_WIDTH, gpu::VRAM_HEIGHT, 0, &window, &renderer);

        SDL_Texture* rgb24texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, gpu::VRAM_WIDTH, gpu::VRAM_HEIGHT);
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XBGR1555, SDL_TEXTUREACCESS_STREAMING, gpu::VRAM_WIDTH, gpu::VRAM_HEIGHT);

        config.bios = "C:\\Users\\Jarrod Norwell\\Documents\\Mandarine\\bios\\SCPH1001.BIN";

        auto system = tools::reset();
        tools::load(system, "C:\\Users\\Jarrod Norwell\\Downloads\\Crash Bandicoot\\Crash Bandicoot.bin");
        system->state = System::State::run;

        sound::init();

        SDL_Event event{};

        while (!token.stop_requested()) {
            while (SDL_PollEvent(&event))
                if (event.type == SDL_EVENT_QUIT)
                    exit(0);

            system->gpu->clear();
            system->controller->update();

            system->emulateFrame();

            SDL_RenderClear(renderer);

            SDL_FRect frect{
                system->gpu->displayAreaStartX,
                system->gpu->displayAreaStartY,
                system->gpu->gp1_08.getHorizontalResoulution(),
                system->gpu->gp1_08.getVerticalResoulution()
            };

            SDL_Rect rect{
                system->gpu->displayAreaStartX,
                system->gpu->displayAreaStartY,
                std::max(640, system->gpu->gp1_08.getHorizontalResoulution()),
                std::max(480, system->gpu->gp1_08.getVerticalResoulution())
            };

            SDL_SetWindowSize(window, rect.w, rect.h);

            if (system->gpu->gp1_08.colorDepth == gpu::GP1_08::ColorDepth::bit24) {
                SDL_UpdateTexture(rgb24texture, &rect, system->gpu->vram.data(), gpu::VRAM_WIDTH * sizeof(uint32_t));
                SDL_RenderTexture(renderer, rgb24texture, &frect, &frect);
            }
            else {
                SDL_UpdateTexture(texture, &rect, system->gpu->vram.data(), gpu::VRAM_WIDTH * sizeof(uint16_t));
                SDL_RenderTexture(renderer, texture, &frect, &frect);
            }

            SDL_RenderPresent(renderer);

            limitFramerate(true, system->gpu->isNtsc());
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }).join();

    return 0;


    // QApplication a(argc, argv);
        
    // MainWindow window;
    // window.show();

    // return a.exec();
}