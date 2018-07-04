# Vetulus
Choose data structures and earn them as a service.

[![Build Status](https://travis-ci.org/pantuza/vetulus.svg?branch=master)](https://travis-ci.org/pantuza/vetulus)
[![Coverage Status](https://coveralls.io/repos/github/pantuza/vetulus/badge.svg?branch=master)](https://coveralls.io/github/pantuza/vetulus?branch=master)
[![Docker Build Status](https://img.shields.io/docker/build/jrottenberg/ffmpeg.svg)](https://hub.docker.com/r/pantuza/vetulus/)
[![GPL licensed](https://img.shields.io/badge/license-GPL-blue.svg)](https://github.com/pantuza/vetulus/blob/master/LICENSE)

## How it works
Create a protobuffer and give it to Vetulus.
Choose a data structure that will store and handle it for you as a service. 

Let's take a look at an example: 
> Imagine you have the following data about people: (name, gender, age).
> You need to store them ordered by age.
> Well, we can use a Queue data structure to dinamically organize data as olderly always goes on the front of the Queue.
> With that, Vetulus gives to you an gRPC interface that implements the methods of this data structure. In our example, 
> you will earn Enqueue, Dequeue, Size methods and etc. 

Vetulus is your **data structure as a service**.

See [documentation (coming soon)]() for more details and usage.

## Getting started

You can check vetulus service by simply running:

```bash
$> docker run --rm pantuza/vetulus
```
then you have a service running ready to receive requests.

Checkout the example [video (coming soon)]() and the [tutorial (coming soon)]()


## How to contribute

Please check the
[Contributing](https://github.com/pantuza/vetulus/blob/master/CONTRIBUTING.md) file.
