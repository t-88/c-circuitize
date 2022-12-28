#include <SDL.h>
#include "wire_manager.h"
#include "utility.h"


static void wire_manager__render(struct WireManager *_) {
    for (size_t i = 0; i < _->wires_count; i++)
        _->wires[i].render(_->wires[i]);
    for (size_t i = 0; i < _->input_port_count; i++)
        _->input_ports[i].render(_->input_ports[i]);
    for (size_t i = 0; i < _->output_port_count; i  ++)
        _->output_ports[i].render(_->output_ports[i]);
}

static void wire_manager__event(struct WireManager *_) {
    for (size_t i = 0; i < _->input_port_count; i++){
        _->input_ports[i].event(&_->input_ports[i]);
    }
    for (size_t i = 0; i < _->output_port_count; i++){
        _->output_ports[i].event(&_->output_ports[i]);
    }
}

static void wire_manager__cleanUp(struct WireManager *_) {
    free(_->wires);
    for (size_t i = 0; i < _->connections_count; i++){
        free(_->connections[i]);
    }
    free(_->connections);
    free(_->input_ports);
    free(_->output_ports);

}

static void wire_manager__add_connection(struct WireManager *_,int input_id, int output_id) {
    for (size_t i = 0; i < _->connections_count; i++){
        if(_->connections[i][0] == input_id) {
            int exist = false;
            for (size_t j = 0; j < _->connections[i][1]; j++){
                if(_->connections[i][j + 2] == output_id) {
                    exist = true;   
                    break;
                }
        }
            if(!exist) {
                _->wires_count++;                 
                _->wires = realloc(_->wires,_->wires_count * sizeof(struct Wire));
                _->wires[_->wires_count - 1] = Wire.new(_->getPort(_,_->connections[i][0],PortType_input)->rect,
                                                        _->getPort(_,output_id,PortType_output)->rect,
                                                        input_id,
                                                        output_id
                                                        );

                _->connections[i][1]++;                 
                _->connections[i] = realloc(_->connections[i],_->connections[i][1] * sizeof(int));
                _->connections[i][_->connections[i][1] + 2 - 1] = output_id;
            }
            break;

        }
    }

    for (size_t i = 0; i < _->connections_output_to_input_count; i++){
        if(_->connections_output_to_input[i][0] == output_id) {
            int exist = false;
            for (size_t j = 0; j < _->connections_output_to_input[i][1]; j++){
                if(_->connections_output_to_input[i][j + 2] == input_id) {
                    exist = true;   
                    break;
                }
        }
            if(!exist) {
                _->connections_output_to_input[i][1]++;                 
                _->connections_output_to_input[i] = realloc(_->connections_output_to_input[i],_->connections_output_to_input[i][1] * sizeof(int));
                _->connections_output_to_input[i][_->connections_output_to_input[i][1] + 2 - 1] = input_id;
            }
            break;

        }
    }    
}
static void wire_manager__delete_connection(struct WireManager* _,int input_id,int output_id) {
    int connection_removed = false;
    
    
    
    for (size_t i = 0; i < _->connections_count; i++){
        if(connection_removed) {
            break;
        }
        if(_->connections[i][0] == input_id) {
            for (size_t j = 0; j < _->connections[i][1]; j++){
                if(_->connections[i][j + 2] == output_id) {

                    for (size_t x = j; x < _->connections[i][1] - 1; x++){
                        _->connections[i][x + 2] = _->connections[i][x + 3];
                    }
                    _->connections[i][1]--;
                    _->connections[i] = realloc(_->connections[i],_->connections[i][1] + 2 * sizeof(int));
                    connection_removed = true;
                    break;
                }
            }
        }
    }   
    connection_removed = false;
    for (size_t i = 0; i < _->connections_output_to_input_count; i++){
        if(connection_removed) {
            break;
        }
        if(_->connections_output_to_input[i][0] == output_id) {
            for (size_t j = 0; j < _->connections_output_to_input[i][1]; j++){
                if(_->connections_output_to_input[i][j + 2] == input_id) {

                    for (size_t x = j; x < _->connections_output_to_input[i][1] - 1; x++){
                        _->connections_output_to_input[i][x + 2] = _->connections_output_to_input[i][x + 3];
                    }
                    _->connections_output_to_input[i][1]--;
                    _->connections_output_to_input[i] = realloc(_->connections_output_to_input[i],_->connections_output_to_input[i][1] + 2 * sizeof(int));
                    
                    connection_removed = true;
                    break;
                }
            }
        }
    }    
}
static void wire_manager__delete_wire(struct WireManager* _,int index) {
    _->deleteConnection(_,_->wires[index].input_id,_->wires[index].output_id);
    _->getPort(_,_->wires[index].output_id,PortType_output)->isActive = false;  
    
    for (size_t i = index; i < _->wires_count - 1; i++){
        _->wires[i] = _->wires[i + 1];
    }
    _->wires_count--;
    _->wires = realloc(_->wires,_->wires_count * sizeof(struct Wire));

}


static struct Port* wire_manager__get_port(struct WireManager *_,int id,int type) {
    struct Port* port = NULL;
    int found = false;
    
    switch (type)
    {
    case PortType_input:
        for (size_t i = 0; i < _->input_port_count; i++){
            if(id == _->input_ports[i].base.id) {
                found = true;
                port = &_->input_ports[i].base;
                break;
            }
        }
        
        break;
    case PortType_output:
        for (size_t i = 0; i < _->output_port_count; i++){
            if(id == _->output_ports[i].base.id) {
                found = true;
                port = &_->output_ports[i].base;
                break;
            }
        }
    break;
    
    default:
        SDL_Log("wire manager: getPort unkown port type");
    }
    if(!found) {
        SDL_Log("wire manager: getPort port not found");
    } 
    return port;
}
static struct InputPort* wire_manager__add_input_port(struct WireManager *_,int x , int y, int w , int h) {
    _->input_port_count++;
    _->input_ports = realloc(_->input_ports,_->input_port_count * sizeof(struct InputPort));
    
    _->connections_count++;
    _->connections = realloc(_->connections,_->connections_count * sizeof(int*));
    _->connections[_->connections_count - 1] = malloc(0);
    _->connections[_->connections_count - 1] = realloc(_->connections[_->connections_count - 1],2 * sizeof(int));


    _->input_ports[_->input_port_count - 1] = InputPort.new(x,y,w,h);
    _->connections[_->connections_count - 1][0] = _->input_ports[_->input_port_count - 1].base.id;
    _->connections[_->connections_count - 1][1] = 0;

    return &_->input_ports[_->input_port_count - 1];

}
static struct OutputPort* wire_manager__add_output_port(struct WireManager *_,int x , int y, int w , int h) {
    _->output_port_count++;
    _->output_ports = realloc(_->output_ports,_->output_port_count * sizeof(struct OutputPort));


    _->connections_output_to_input_count++;
    _->connections_output_to_input = realloc(_->connections_output_to_input,_->connections_output_to_input_count * sizeof(int*));
    _->connections_output_to_input[_->connections_output_to_input_count - 1] = malloc(0);
    _->connections_output_to_input[_->connections_output_to_input_count - 1] = realloc(_->connections_output_to_input[_->connections_output_to_input_count - 1],2 * sizeof(int));


    _->output_ports[_->output_port_count - 1] = OutputPort.new(x,y,w,h);
    _->connections_output_to_input[_->connections_output_to_input_count - 1][0] = _->output_ports[_->output_port_count - 1].base.id;
    _->connections_output_to_input[_->connections_output_to_input_count - 1][1] = 0;


    return &_->output_ports[_->output_port_count - 1];

}


static void wire_manager__manage_port_activation(struct WireManager *_) {
    for (size_t i = 0; i < _->connections_count; i++){
        int isActive = _->getPort(_,_->connections[i][0],PortType_input)->isActive; 
        for (size_t j = 0; j < _->connections[i][1]; j++){
            _->getPort(_,_->connections[i][j + 2],PortType_output)->isActive = isActive;
        }
    }
}
static void wire_manager__update(struct WireManager *_) {
    for (size_t i = 0; i < _->input_port_count; i++){
        _->input_ports[i].update(&_->input_ports[i]);
    }
    for (size_t i = 0; i < _->output_port_count; i++){
        _->output_ports[i].update(&_->output_ports[i]);
    }
    for (size_t i = 0; i < _->wires_count; i++){
        _->wires[i].update(&_->wires[i]);
    }

    for (size_t i = 0; i < _->wires_count; i++){
        if(_->wires[i].requestToDelete) {
            _->deleteWire(_,i);
            break;
        }
    }

    _->managePortActivation(_);

    _->didUpdateOnePort = false;

}

struct WireManager wire_manager__new() {
    struct WireManager _;
    _.input_ports = malloc(0);       
    _.output_ports = malloc(0);       
    _.connections = malloc(0);
    _.wires = malloc(0);
    _.connections_output_to_input = malloc(0);
    

    _.update = &wire_manager__update;
    _.render = &wire_manager__render;
    _.event = &wire_manager__event;
    _.addInputPort = &wire_manager__add_input_port;
    _.addOutputPort = &wire_manager__add_output_port;
    _.addConnection = &wire_manager__add_connection;
    _.getPort = &wire_manager__get_port;
    _.cleanUp = &wire_manager__cleanUp;
    _.deleteWire  = &wire_manager__delete_wire;
    _.deleteConnection  = &wire_manager__delete_connection;
    _.managePortActivation  = &wire_manager__manage_port_activation;
    

    _.input_port_count = 0;
    _.output_port_count = 0;
    _.connections_count = 0;
    _.wires_count = 0;
    _.connections_output_to_input_count = 0;

    _.ableToSelectPort = true;
    _.curr_port_id = -1;

    _.didUpdateOnePort = false;

    return _;
}
const struct WireManagerClass WireManager = {.new = &wire_manager__new};