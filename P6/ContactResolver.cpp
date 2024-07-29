#include "ContactResolver.h"
#include "ParticleContact.h"
#include <iostream>

using namespace physics;

void ContactResolver::ResolveContacts(std::vector<ParticleContact*> contacts, float time)
{
    if (contacts.empty()) {
        return; // or throw an exception, depending on your requirements
    }
    current_iterations = 0;

    //std::cout << "hatdog" << std::endl;

    while (current_iterations < max_iterations) {
        unsigned int curr_index = 0;
        float minSeparatingSpeed = contacts[0]->GetSeparatingSpeed(); // initialize with a large value
        float max_depth = contacts[0]->depth; // initialize with a small value

        for (unsigned i = 0; i < contacts.size(); i++) {
            float separatingSpeed = contacts[i]->GetSeparatingSpeed();

            if (separatingSpeed <= minSeparatingSpeed && separatingSpeed < 0) {
                curr_index = i;
                minSeparatingSpeed = separatingSpeed;


                if (max_depth < contacts[i]->depth) {
                    max_depth = contacts[i]->depth;
                }
            }
        }

        if (minSeparatingSpeed >= 0 && max_depth <= 0) {
            break; // or return, depending on your requirements
        }

        contacts[curr_index]->Resolve(time);
        current_iterations++;
    }
}
