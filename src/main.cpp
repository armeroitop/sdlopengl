#define GLM_ENABLE_EXPERIMENTAL
#include "app/app.hpp"

int main(int argc, char* argv []) {

    App app;

    app.init();

    app.run();

    app.shutdown();

    return 0;
}
