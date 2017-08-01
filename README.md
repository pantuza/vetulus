# Vetulus
Choose data structures and earn them as a service.

[![Build Status](https://travis-ci.org/pantuza/vetulus.svg?branch=master)](https://travis-ci.org/pantuza/vetulus)

## How it works
Create a protobuffer or message-pack and give it to Vetulus.
Choose a data structure that will store and handle it for you. 

Let's take a look at a example: Imagine you have the following data about people (name, gender, age).
You need to store them as a familly relations.
Well, we can use a graph data structure to dinamically organize data as who is a father and who is a son.
With that, you will have a API and gRPC that implements the methods of this data structure for you.
