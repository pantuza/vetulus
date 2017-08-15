# Vetulus
Choose data structures and earn them as a service.

[![Build Status](https://travis-ci.org/pantuza/vetulus.svg?branch=master)](https://travis-ci.org/pantuza/vetulus)
[![Coverage Status](https://coveralls.io/repos/github/pantuza/vetulus/badge.svg?branch=master)](https://coveralls.io/github/pantuza/vetulus?branch=master)
[![GPL licensed](https://img.shields.io/badge/license-GPL-blue.svg)](https://github.com/pantuza/vetulus/blob/master/LICENSE)

## How it works
Create a protobuffer or message-pack and give it to Vetulus.
Choose a data structure that will store and handle it for you. 

Let's take a look at an example: 
> Imagine you have the following data about people: (name, gender, age).
> You need to store them ordered by age.
> Well, we can use a Queue data structure to dinamically organize data as olderly always goes on the front of the Queue.
> With that, Vetulus gives to you an API and gRPC that implements the methods of this data structure. In our example, 
> you will earn Enqueue, Dequeue, Size methods and etc. 

Vetulus is your **data structure as a service**.

## How to contribute

Please check the
[Contributing](https://github.com/pantuza/vetulus/blob/master/CONTRIBUTING.md) file.
