# Pugl LV2 UI Host Example

Example app to load an LV2 plugin UI in a Pugl parent view.


### Build and run:
To clone & build:
```
git clone --recursive https://github.com/ctsexton/pugl_host_example.git
cd pugl_host_example
mkdir build && cd build
cmake ..
make
```

To run:
```
./PuglHost <plugin_uri>
```
OR, to load a dummy pugl child view, a blue box inside the red parent box:
```
./PuglHost DUMMY_CHILD
```
