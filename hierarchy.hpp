// (c) Daniel Dennis 2018

// Implements and manages an object hierarchy, provides methods
// To message individual nodes in hierarchy and its children
// Object heirarchy type and packet in which data is sent
// needs to be specified, (hierarchy_implementation) does this
// Everything in this class is my own work

#ifndef HIERARCHY_HPP
#define HIERARCHY_HPP

#include <vector>
#include <stack>
#include <iostream>
#include <cstdint>

namespace dd
{
    typedef uint16_t id_t; // Node ID is array of 16 bit unsigned integers
    typedef std::stack<id_t> traverse_id_t; // Node ID for internal use
    typedef std::vector<id_t> node_id_t; // Node ID for external use

    template<class T, typename packet> class hierarchy
    {
    private:
    // Variables and objects
        id_t this_id, this_depth;
        std::vector<class hierarchy*> children;

    protected:
    // Methods
        void propogate_to_children(packet data)
        {
            for(int i = 0; i < children.size(); i++)
            {
                children[i]->node.set_parent(data);
                children[i]->propogate_to_children(data);
            }   
        }
        
        traverse_id_t traverse(traverse_id_t current_layer)
        {
            current_layer.pop();
            id_t child_id;
            traverse_id_t return_id;

            if(current_layer.size())
            {
                child_id = current_layer.top();
                return_id = children[child_id]->traverse(current_layer);
                return_id.push(this_id);
                return return_id;
            }
            else
            {
                child_id = children.size();
                class hierarchy* new_child = new class hierarchy(child_id);
                children.push_back(new_child);
                return_id.push(child_id);
                return_id.push(this_id);
                return return_id;
            }
        }

        void set_element_internal(traverse_id_t address, packet data)
        {
            address.pop();

            if(address.size())
            {
                return children[address.top()]->set_element_internal(address, data);
            }
            else
            {
                broadcast_internal(data);
                return;
            }
        }
        
        void broadcast_internal(packet data)
        {
            node.set(data);
            data = node.get(data);
            for(int i = 0; i < children.size(); i++)
            {
                children[i]->broadcast_internal(data);
            }
            return;
        }

    public:
    // Variables and objects
        T node;

    // Constructors
        hierarchy(){}
        hierarchy(id_t id){this_id = id;}
        ~hierarchy(){for(int i = 0; i < children.size(); i++) delete children[i];}
    
    // Methods
        node_id_t insert_element(node_id_t address)
        {
            traverse_id_t new_id, traverse_return;
            
            for(int i = (address.size() - 1); i >= 0; i--)
            {
                new_id.push(address[i]);
            }

            address.clear();

            traverse_return = traverse(new_id);
            node_id_t return_id;

            while(traverse_return.size())
            {
                return_id.push_back(traverse_return.top());
                traverse_return.pop();
            }

            return return_id;
        }

        node_id_t create_family(int id = 0)
        {
            node_id_t return_id;
            this_id = id;
            if(children.empty() == false)
            {
                std::cerr << "Error: family already initialised\n"; // throw exception here?
                return return_id;
            }
            else
            {
                return_id.push_back(0);
                return return_id;
            }
        }

        void set_element(node_id_t address, packet data)
        {
            traverse_id_t traverse_id;
            for(int i = (address.size() - 1); i >= 0; i--)
            {
                traverse_id.push(address[i]);
            }

            set_element_internal(traverse_id, data);

            return;
        }

        void broadcast(packet data)
        {
            broadcast_internal(data);
            return;
        }
    };
}

#endif