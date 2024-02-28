FROM ghcr.io/rikorose/gcc-cmake:gcc-13
COPY . /usr/src/agileapp
WORKDIR /usr/src/agileapp/cpp_task_2D_plane/build
RUN cmake ..
RUN make -j8
CMD ["./server","-n","5","-t","3333","-s","4444"]