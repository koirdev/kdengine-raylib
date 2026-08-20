import os, sys, platform
# Writing OS/Hardware information into variables
PYTHON_VERSION = platform.python_version()
OS_NAME = os.name # OS Name
PLATFORM_SYS = platform.system() # Platform system
PLATFORM_RELEASE = platform.release() # Platform release
PLATFORM_VERSION = platform.version() # Platform version
PLATFORM_ARCH = platform.architecture() # Platform architecture


print(f"OS Info:\nPython version: '{PYTHON_VERSION}'\nPlatform system: '{PLATFORM_SYS}'\nPlatform release: '{PLATFORM_RELEASE}'\nPlatform version: '{PLATFORM_VERSION}'\nPlatform architecture: '{PLATFORM_ARCH}'")