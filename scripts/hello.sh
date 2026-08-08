#!/bin/bash

# Get the root directory of the project.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

# Build directory and executable.
BUILD_DIR="$PROJECT_DIR/bld"
EXECUTABLE="$BUILD_DIR/hello"


# Remove the existing build directory and create a clean build.
build()
{
    rm -rf "$BUILD_DIR" || exit 1

    cmake -S "$PROJECT_DIR" -B "$BUILD_DIR" || exit 1
    cmake --build "$BUILD_DIR" || exit 1
}


# Open a new terminal and run the application.
run()
{
    gnome-terminal -- bash -c "\"$EXECUTABLE\"; exec bash"
}


# Kill the running application.
kill_app()
{
    pkill -x hello
}


# Handle the requested command.
case "$1" in
    build)
        build
        ;;
    run)
        run
        ;;
    kill)
        kill_app
        ;;
    *)
        echo "Usage: $0 {build|run|kill}"
        exit 1
        ;;
esac
