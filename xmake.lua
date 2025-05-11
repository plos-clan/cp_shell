set_project("CPShell")
add_rules("mode.debug", "mode.release")
set_optimize("fastest")
set_languages("c23")
set_warnings("all", "extra")
set_policy("run.autobuild", true)

target("cplibc")
    set_kind("static")
    set_toolchains("clang")

    local base_dir = "submod/cplibc"
    add_files(base_dir.."/src/*.c")
    add_includedirs(base_dir.."/include", {public = true})
    add_cflags("-nostdlib", "-fno-stack-protector")

target("pl_readline")
    set_kind("static")
    set_toolchains("clang")

    local base_dir = "submod/libpl_readline"
    add_files(base_dir.."/src/*.c")
    add_includedirs(base_dir.."/include", {public = true})

    add_defines("PL_ENABLE_HISTORY_FILE=0")
    add_cflags("-mno-80387", "-mno-mmx", "-DNDEBUG")
    add_cflags("-mno-sse", "-mno-sse2", "-mno-red-zone")
    add_cflags("-nostdlib", "-fno-builtin", "-fno-stack-protector")

target("shell")
    set_kind("binary")
    set_default(false)
    add_deps("cplibc","pl_readline")
    set_toolchains("clang")

    add_files("src/*.c")
    add_includedirs("include")
    add_includedirs("submod/cplibc/include")
    add_includedirs("submod/cplibc/include/types")
    add_cflags("-nostdlib","-nostdinc","-fno-stack-protector", "-g")
    add_ldflags("-nostdlib")

    before_build(function (target)
        local hash = try { function() return os.iorun("git rev-parse --short HEAD") end }
        if hash then
            hash = hash:trim()
            target:add("defines", "GIT_VERSION=\"" .. hash .. "\"")
        end
    end)

    add_links("cplibc")

    add_ldflags("-Wl,--whole-archive", "-lcplibc", {force = true})

target("shellt")
    set_kind("phony")
    add_deps("shell")
    set_default(true)

    on_build(function (target)
        import("core.project.project")
        local shell = project.target("shell")
        os.cp(shell:targetfile(), "shell.elf")
    end)



