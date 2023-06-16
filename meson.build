# set the project name and language
project('Myzdin', 'c',  default_options: 'c_std=c17', license: 'BSD 3-Clause', meson_version: '>=0.61.2', version: 'alpha')

# set the environment for the project (Release, Debug)
env = 'Debug'

# default c flags
c_flags = []

# set C flags according to environment
if env == 'Release'
    c_flags = ['-Wall', '-Wswitch-default', '-Wno-unknown-pragmas', '-Wpedantic', '-Wextra', '-Werror', '-O2']
elif env == 'Debug'
    c_flags = ['-Wall', '-Wswitch-default', '-Wno-unknown-pragmas', '-Wpedantic', '-Wextra', '-Werror']
endif

# get current build directory
build_dir = meson.current_build_dir()

# set source files
src_files = files('src/main.c', 'src/scene/scene.c', 'src/keybindings/keybindings.c', 'src/boundaries/boundaries.c', 'src/collision/collision.c')

# set linker options
linker_options = ['-lSDL2', '-lSDL2_mixer', '-lSDL2_image']

# copy the assets directory to the build directory
run_command('cp', '-r', 'assets', build_dir, check: true)

# add an executable consisting of the specified source files, dependencies, link options, and c flags
executable('Myzdin'
    , src_files
    , link_args: linker_options
    , c_pch: 'src/pch/myzdin-pch.h'
    , c_args: c_flags
)

clangtidy = find_program('clang-tidy', required: false)

if clangtidy.found()
    run_target(
        'tidy',
        command: [
            clangtidy,
            '-checks=*,clang-analyzer-*,-llvm-*,-llvmlibc-*,-hicpp-*,-altera-*',
            '-header-filter=.*',
            '-p',
            meson.project_build_root(),
        ] + src_files)
endif
