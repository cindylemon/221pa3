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

    if (w <= 0 || h <= 0) {
        return nullptr;
    }

    Node* node = new Node(s, ul, w, h);

    if (w == 1 && h == 1) {
        node->A = nullptr;
        node->B = nullptr;
        node->C = nullptr;
        return node;
    }

    bool canSplitHorizontally = (h >= 2);
    bool canSplitVertically = (w >= 2);

    if (!canSplitHorizontally && !canSplitVertically) {
        node->A = nullptr;
        node->B = nullptr;
        node->C = nullptr;
        return node;
    }
 
    // If colour variability of a node is at most the tolerance, then we can simply not construct any children for this node
    if (node->var <= tol) {
        node->A = nullptr;
        node->B = nullptr;
        node->C = nullptr;
        return node;
    }

    bool splitHorizontally;
    
    if (h == 1) {
        splitHorizontally = false;
    } else if (w == 1) {
        splitHorizontally = true;
    } else {
        splitHorizontally = (h > w);
    }

    // splitting horizontally 
    if (splitHorizontally) {
        if (h >= 3) {
            int p = h/3;
            int remainder = h % 3;

            int heightA;
            int heightB;
            int heightC;

            if (remainder == 0) {
                heightA = p;
                heightB = p;
                heightC = p;
            } else if (remainder == 1) {
                heightA = p;
                heightB = p + 1;
                heightC = p;
            } else {
                heightA = p + 1;
                heightB = p;
                heightC = p + 1;
            }

            node->A = BuildTree(s, ul, w, heightA, tol);
            node->B = BuildTree(s, make_pair(ul.first, ul.second + heightA), w, heightB, tol);
            node->C = BuildTree(s, make_pair(ul.first, ul.second + heightA + heightB), w, heightC, tol);
        } else if (h == 2) {
            int heightA = 1;
            int heightB = 1;

            node->A = BuildTree(s, ul, w, heightA, tol);
            node->B = BuildTree(s, make_pair(ul.first, ul.second + heightA), w, heightB, tol);
            node->C = nullptr;
        } 
    } else { // split vertically
        if (w >= 3) {
            int p = w/3;
            int remainder = w % 3;

            int widthA;
            int widthB;
            int widthC;

            if (remainder == 0) {
                widthA = p;
                widthB = p;
                widthC = p;
            } else if (remainder == 1) {
                widthA = p;
                widthB = p + 1;
                widthC = p;
            } else {
                widthA = p + 1;
                widthB = p;
                widthC = p + 1;
            }
        
            node->A = BuildTree(s, ul, widthA, h, tol);
            node->B = BuildTree(s, make_pair(ul.first + widthA, ul.second), widthB, h, tol);
            node->C = BuildTree(s, make_pair(ul.first + widthA + widthB, ul.second), widthC, h, tol);
        } else if (w == 2) {
            int widthA = 1;
            int widthB = 1;
            
            node->A = BuildTree(s, ul, widthA, h, tol);
            node->B = BuildTree(s, make_pair(ul.first + widthA, ul.second), widthB, h, tol);
            node->C = nullptr;
        }
    }

    return node;
}

/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    if (root == nullptr) {
        return PNG();
    }
    PNG output;
    output.resize(root->width, root->height);
    Render_Helper(root, output);
    return output;
}

/**
 * Delete allocated memory.
**/
void ThreeTree::Clear() {
    Clear_Helper(root);
}

/**
 * Copy other tree into this tree object.
**/
void ThreeTree::Copy(const ThreeTree& other) {
    root = Copy_Helper(other.root);
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
    return NumLeaves_Helper(root);
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**/
void ThreeTree::RotateCW() {
    if (root == nullptr) {
        return;
    }

    Rotate_Helper(root, root->height, root->width);
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

void ThreeTree::Clear_Helper(Node* subroot) {
    if(subroot == nullptr) return;
    Clear_Helper(subroot->A);
    Clear_Helper(subroot->B);
    Clear_Helper(subroot->C);
    delete subroot;
    subroot = nullptr;
}

Node* ThreeTree::Copy_Helper(Node* subroot) {
    if (subroot == nullptr) return nullptr;
    Node* newNode = new Node(subroot->upleft, subroot->width, subroot->height, subroot->avg, subroot->var);
    newNode->A = Copy_Helper(subroot->A);
    newNode->B = Copy_Helper(subroot->B);
    newNode->C = Copy_Helper(subroot->C);
    return newNode;
}

void ThreeTree::Render_Helper(Node* subroot, PNG& output) const {
    if (subroot == nullptr) {
        return;
    }
    if (subroot->A == nullptr && subroot->B == nullptr && subroot->C == nullptr) {
        int xOrigin = subroot->upleft.first;
        int yOrigin = subroot->upleft.second;
        int w  = subroot->width;
        int h  = subroot->height;

        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                RGBAPixel* p = output.getPixel(xOrigin + i, yOrigin + j);
                *p = subroot->avg;
            }
        }
        return;
    }
    Render_Helper(subroot->A, output);
    Render_Helper(subroot->B, output);
    Render_Helper(subroot->C, output);
}

void ThreeTree::Rotate_Helper(Node* subroot, int newW, int newH) {
    auto isBefore = [](Node* a, Node* b) {
        if (a->upleft.second < b->upleft.second) return true;
        if (a->upleft.second > b->upleft.second) return false;
        return a->upleft.first < b->upleft.first;
    };


    if (subroot == nullptr) {
        return;
    }

    int prevX = subroot->upleft.first;
    int prevY = subroot->upleft.second;
    int prevW = subroot->width;
    int prevH = subroot->height;

    int newX = newW - (prevY + prevH);
    int newY = prevX;

    subroot->upleft = { newX, newY };
    subroot->width  = prevH;
    subroot->height = prevW;

    Rotate_Helper(subroot->A, newW, newH);
    Rotate_Helper(subroot->B, newW, newH);
    Rotate_Helper(subroot->C, newW, newH);
    
    Node* A = subroot->A;
    Node* B = subroot->B;
    Node* C = subroot->C;

    if (A == nullptr) { 
        Node* t = A;
        A = B;
        B = t; 
    }
    if (A == nullptr) {
         Node* t = A;
         A = C;
         C = t; 
    }
    if (B == nullptr) { 
        Node* t = B;
        B = C; 
        C = t;
    }

    if (A && B && !isBefore(A, B)) {
    Node* t = A; A = B; B = t;
    }

    if (B && C && !isBefore(B, C)) {
        Node* t = B; B = C; C = t;
    }

    if (A && B && !isBefore(A, B)) {
        Node* t = A; A = B; B = t;
    }

    subroot->A = A;
    subroot->B = B;
    subroot->C = C;
}