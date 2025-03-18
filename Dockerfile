# Use an official Ubuntu base image
FROM ubuntu:22.04

# Set the working directory inside the container
WORKDIR /app

# Install required dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

# Copy all files (including Makefile) into the container
COPY . .

# Run the Makefile to build the project
RUN make

# Set the default command to execute the program
CMD ["./lab6"]
