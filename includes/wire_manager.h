#pragma once

#include <SDL.h>
#include "port.h"
#include "wire.h"

struct WireManager {
    struct InputPort *input_ports;
    struct OutputPort *output_ports;
    struct Wire *wires;
    int** connections;
    int** connections_output_to_input;

    

    int input_port_count;
    int output_port_count;
    int connections_count;
    int connections_output_to_input_count;
    int wires_count;
    struct Port *curr_port;

    int ableToSelectPort;
    int curr_port_id;
    int curr_port_type;

    int didUpdateOnePort;

    void (*render) (struct WireManager*_);
    void (*update) (struct WireManager*);
    void (*event) (struct WireManager *_);
    struct InputPort* (*addInputPort) (struct WireManager* _,int x , int y, int w , int h);
    struct OutputPort* (*addOutputPort) (struct WireManager* _,int x , int y, int w , int h);
    void (*addConnection) (struct WireManager* _,int,int);
    struct Port* (*getPort) (struct WireManager* _,int id,int type);
    void (*cleanUp) (struct WireManager *_);
    void (*deleteWire) (struct WireManager *_,int index);
    void (*deleteConnection) (struct WireManager* _,int input_id,int output_id);
    void (*managePortActivation)(struct WireManager* _);
    
    
    
};
extern const struct WireManagerClass {
    struct WireManager (*new) ();
} WireManager;