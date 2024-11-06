# Arguments
AddOption(
    "--release",
    dest = "release",
    default = False,
    help = "Sets the build to release mode"
)

env = Environment()

if GetOption("release"):
    env.Append(CCFLAGS = ["-O2"])
else:
    env.Append(CCFLAGS = [])


Export("env")

# Main program
SConscript("src/SConscript")

# Lang library
SConscript("default-lang/SConscript")