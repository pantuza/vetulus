/*
 * Copyright 2017 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  gate.cc
 *
 *    Description:  The gate that coordinate the workers execution
 *
 *        Version:  1.0
 *        Created:  11/09/2017 14:56:13
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer Science community
 *
 * ============================================================================
 */

#include <signal.h>

#include <iostream>

#include "./gate.h"
#include "./pool.h"


Gate::Gate(WorkersConfigLoader config)
{
    this->threads = stoi(config.threads);
    this->pool = new ThreadPool(this->threads);

    this->console = spd::stdout_color_mt("Gate");
    this->console->info("Welcome to Vetulus Workers Gate");
}


void Gate::listen()
{
    this->pool->arise();
}


void Gate::shutdown()
{
    this->pool->die();
}

/**
 * Callback to handle SIGINT signal when caught
 */
static void sigintCallback(int signal)
{
    cout << "Caught keyboard interruption. Shuting down Vetulus Gate" << endl;
    exit(1);
}




/**
 * Main execution of the API binary
 */
int main(int argc, char* argv[]) {
    string config_file = "/etc/vetulus/workers.conf";

    if (argc > 1) {
        config_file = argv[1];
    }

    signal(SIGINT, sigintCallback);

    WorkersConfigLoader config;
    config.load(config_file);

    Gate gate(config);

    gate.listen();

    return EXIT_SUCCESS;
}
