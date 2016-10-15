FROM ubuntu:xenial
MAINTAINER lelandjansen

RUN apt-get update && apt-get install -y \
	cmake \
	gcc-avr \
	binutils-avr \
	avr-libc \
	avrdude \
	python3.5

# TODO: install qtools and dependencies

