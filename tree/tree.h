/**
 *\file
 *\brief tree struct and changing akinator tree functions
 */

#ifndef TREE_H
#define TREE_H


struct Node
{
    const char *data = nullptr;
    Node *left  = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
};

struct Tree
{
    Node *root = nullptr;//add debug info
};

static unsigned int TREE_ERRNO = 0;

/**
 * Allocates new tree node.
 * \param [in]  data  data to put in node
 * \return            pointer to allocated node
 */
Node *tree_create_node (const char *data = nullptr);

/**
 * Construct tree by allocating tree root.
 * \param [in]  tree  pointer of tree to construct
 * \param [in]  err   pointer to error number code
 */
void tree_ctor (Tree *tree, unsigned int *err = &TREE_ERRNO);

/**
 * Scan input information to buffer.
 * \param [in]       tree         pointer to working tree
 * \param [in, out]  parent_node  node to add in
 * \param [in]       left_case    data of node adding as left of parent_node
 * \param [in]       right_case   data of node adding as right of parent_node
 * \param [in]       err          pointer to error number code
 */
void add_node (Tree *tree, Node *parent_node, const char *left_case, const char *right_case, unsigned int *err = &TREE_ERRNO);

/**
 * Scan input information to buffer.
 * \param [in]  tree  pointer of tree to destruct
 * \param [in]  err   pointer to error number code
 */
void tree_dtor (Tree *tree, unsigned int *err = &TREE_ERRNO);

/**
 * Scan input information to buffer.
 * \param [in]  node pointer of node to free
 */
void tree_free (Node *node);

/**
 * Scan input information to buffer.
 * \param [in]  tree  tree to check
 * \param [in]  err   pointer to error number code
 * \return            error code
 */
unsigned int tree_check (Tree *tree, unsigned int *err);
/**
 * Scan input information to buffer.
 * \param [in]  tree  pointer to working tree
 * \param [in]  err   pointer to error number code
 */
void tree_dump (Tree *tree, unsigned int *err);

/**
 * Scan input information to buffer.
 * \param [in]  tree  pointer to tree for which graph will be made
 */
void tree_graph (Tree *tree);

/**
 * Scan input information to buffer.
 * \param [in]  node         pointer to node for which graph will be made
 * \param [in]  tgraph_file  file to write graphs in
 * \return                   index number of created graph
 */
int make_graph_nodes (Node *node, FILE *tgraph_file);

#endif /* AKINATOR_H */
