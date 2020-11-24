## Possible improvements

#### Theory
- Choose the right feature detection algorithm for the dataset
- Adjust how matches between feature are filtered

#### CI/CD
- Caching CMake and OpenCV installs
- Generate downloadable artifacts (executables, logs, test reports, etc...)
- Improve and add more unit and/or integration tests

#### C++ code
- Add error handling
- Handle different formats (ex: with photos with an alpha channel)
- Refactor the program so it is not one big single function
- Take care of the many TODOs littering the code
- Add batch mode with multithreading to process large amounts of pictures

#### Usability
- Add a GUI to select the ROI
- Allow users to rotate pictures