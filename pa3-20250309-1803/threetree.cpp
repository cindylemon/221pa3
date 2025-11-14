/**
 * @file            threetree.cpp
 * @author          your CWL
 * @description     Implementation of ThreeTree functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "threetree.h"

/**
 * ThreeTree constructor given tolerance for variance.
**/
ThreeTree::ThreeTree(PNG& imIn, double tol) {
    /* Complete your implementation below */
    int width = imIn.width();
    int height = imIn.height();

    Stats s = Stats(imIn);

    root = BuildTree(s, make_pair(0,0), width, height, tol);
}

/**
 * Helper for the ThreeTree constructor.
**/
Node* ThreeTree::BuildTree(Stats& s, pair<int, int> ul, int w, int h, double tol) {
    /* Replace the line below with your implementation */
    return nullptr;
}

/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    /* Replace the line below with your implementation */
    return PNG();
}

/**
 * Delete allocated memory.
**/
void ThreeTree::Clear() {
    /* Complete your implementation below */

    
}

/**
 * Copy other tree into this tree object.
**/
void ThreeTree::Copy(const ThreeTree& other) {
    /* Complete your implementation below */

    
}

/**
 * Returns the number of nodes in the tree
**/
int ThreeTree::Size() const {
    return Size_Helper(root);
}

/**
 * Returns the number of leaf nodes in the tree
**/
int ThreeTree::NumLeaves() const {
    /* Replace the line below with your implementation */
    return 0;
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**/
void ThreeTree::RotateCW() {
    /* Complete your implementation below */

    
}

/*****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN sqtree-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                 *
*****************************************************************/

int ThreeTree::Size_Helper(Node* subroot) const {
    if(subroot == nullptr) return 0;

    return 1 + Size_Helper(subroot->A) + Size_Helper(subroot->B) + Size_Helper(subroot->C);
}

int ThreeTree::NumLeaves_Helper(Node* subroot) const {
    if(subroot == nullptr) return 0;
    if(!subroot->A && !subroot->B && !subroot->C) return 1;

    return NumLeaves_Helper(subroot->A) + NumLeaves_Helper(subroot->B) + NumLeaves_Helper(subroot->C);
    
}