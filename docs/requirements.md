# Browser Compatibility

Rather than come up with minimum versions for every browser I will use this rule: If [caniuse](http://caniuse.com) reports that globally at least 60% and in the US at least 75% of the users can use the feature, then it is OK to use.

The exception is webassembly itself which is currently only around 50% for both global and US usage.

# Extensibility

Each entity created has a set of components. Each component is defined by a .cpp and .hpp file. In order for users to be able to define their own components, and to create a custom build with only required components, there will be a config file "build_components.txt" in the root folder (git ignored) that will contain the list of extra components to be built in addition to the required components (camera, etc). It will just be a list of .cpp file paths for each commponent, and the build script will pick it up and link those into the final assembly. This way the user-defined components can be in another repository.
