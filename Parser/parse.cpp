#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <NetworKit/graph/Graph.h>
#include <iostream>
#include <unordered_map>
using namespace std;
using namespace NetworKit;
#ifdef LIBXML_TREE_ENABLED

/*
 *To compile this file using gcc you can type
 *gcc `xml2-config --cflags --libs` -o xmlexample libxml2-example.c
 */

/*parses the gexf file and builds a graph*/
std::unordered_map<const xmlChar*, node> nodeMap;
void parseGexf(xmlNodePtr a_node, Graph& G)
{
  xmlNodePtr cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
          //replace with switch-case
            if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"graph"))) {
              xmlChar *mode, *isDirected;
              mode = xmlGetProp(cur_node, (const xmlChar *)"mode");
              isDirected = xmlGetProp(cur_node, (const xmlChar *)"defaultedgetype");
              //printf("mode: %s\n", mode);
              //printf("isDirected: %s\n", isDirected);
              if((!xmlStrcmp(isDirected, (const xmlChar *)"directed")))
                G = NetworKit::Graph(0, true, true );
              else
                G = NetworKit::Graph(0, true, false );
              xmlFree(mode);
              xmlFree(isDirected);
            }
            if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"node"))) {
              xmlChar *id;
              id = xmlGetProp(cur_node, (const xmlChar *)"id");
              node u = G.addNode();
              nodeMap.insert(std::make_pair(id,u));
              //printf("id: %s\n", id);
              xmlFree(id);
            }
            if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"edge"))) {
              xmlChar *source, *target, *weight;
              source = xmlGetProp(cur_node, (const xmlChar *)"source");
              target = xmlGetProp(cur_node, (const xmlChar *)"target");
              weight = xmlGetProp(cur_node, (const xmlChar *)"weight");
              node u = nodeMap[source];
              node v = nodeMap[target];
              G.addEdge(u, v);
              if(weight != NULL)
                G.setWeight(u, v, strtol((char*)weight, NULL, 0));
              //printf("source: %s\n", source);
              //printf("source: %s\n", target);
              xmlFree(source);
              xmlFree(target);
              xmlFree(weight);
            }

        }

        parseGexf(cur_node->children, G);
    }
}

int main(int argc, char **argv)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    Graph G;
    if (argc != 2)
        return(1);

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    parseGexf(root_element, G);
    cout << "Graph generated: " << G.toString() << endl;
    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return 0;
}
#else
int main(void) {
    fprintf(stderr, "Tree support not compiled in\n");
    exit(1);
}
#endif
