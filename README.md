# 3DS Typer

A 3DS game in which you need to destroy Comets to protect your base by swiftly pressing keys on your console.

## How is it made

This game in written in C++ using the DevKitPro toolkit by the 3DS Homebrew community.
Thanks to the <citro2d> and <citro3d> libs, using the GPU on the 3DS is extremly easy just like raylib.

## Get this running

To compile the project simply run `make` at the root of the project (where the `Makefile` is).

Ensure the you have the devkitpro environment already setup. Refer to their website for more info.

After compiling, you will see a `3ds-type.3dsx` file in the project directory. This is a homebrew application meant to be run in the homebrew launcher on an actual 3DS.
Though, we can run this on an emulator too if you don't have an actual 3DS handy.

The project has three tasks defined in the `.zed/tasks.json` file for the Zed editor. It can be adapted to any tasking system.

1. Make -> This will simply run `make` and compile the homebrew application.
2. Run in Mandarine -> This will make and run the game in the `mandarine` 3DS emulator. You can use any emulator of you liking, that supports `.3dsx` file loading.
3. Run on 3DS -> This will make and run game on an actual 3DS using `3dslink`.

For step 3 to work, you would need to have an actual homebrew'd 3DS on the same network running homebrew launcher in link mode (press Y in the launcher). The game will automatically launch on your console.

To exit the game, press `START`

## Roadmap

- [ ] Learn C++
- [ ] Familiarize with 3DS homebrew app lifecycle
- [ ] Figure out drawing shapes with citro2d
- [ ] Basic game logic
- [ ] Implement game loop
- [ ] Draw text
- [ ] Add some sound (music + fx)
- [ ] Make this actually feel like a game
- [ ] Figure out bottom screen use
- [ ] Add icons
- [ ] Publish to the universal store/h-shop/homebrew store/
- [ ] Make the C++ code more structures (create other cpp files and header files)

## Why made this

Just to revive my game dev skills and actually make some games for the 3DS. This one is a very simple project. I plan to make more game/apps in future.

## Legal Notice

This software is not affiliated, endorsed, or licensed by Nintendo Co., Ltd. Nintendo 3DS is a trademark of Nintendo.

This project is for educational and research purposes only, and should not be used to promote or facilitate software piracy.

All rights to the Nintendo 3DS™ hardware and related trademarks belong to Nintendo Co., Ltd.
