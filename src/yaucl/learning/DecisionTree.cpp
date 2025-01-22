//
// Created by giacomo on 02/12/24.
//

#include <yaucl/learning/DecisionTree.h>


void DecisionTree::splitTree(bool dooblique) {
    /**
     * This implementation follows the lead of the following BuildTree function from the following repository:
     * https://github.com/christophmeyer/twigy/blob/master/src/core/decision_tree.cpp
     *
     * Copyright (c) 2020 Christoph Meyer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
     */
    std::stack<size_t> currentNode;
    children.emplace_back(0, dr.max_record_size, 0);
    currentNode.push(0);
    size_t curr = 0;
    size_t idx = 0;
    union_minimal missing_val_dbl = 0.0;
    union_minimal missing_val_str = "";
    while (!currentNode.empty()) {
        std::cerr << "start " << (idx++) << std::endl;
        curr = currentNode.top();
        auto& node = children[curr];
        dr.forthegain.reset();

        if ((node.split == 0) && (node.rightOffset == 0)) {
            std::cerr << "start " << (idx++) << std::endl;
            size_t N = node.end - node.begin;
//                std::cout << node.begin << "---"<<node.end << std::endl;

            double purity = 0.0;
            int clazz = -1;

            std::cerr << "iteration over  " << node.end << ": " << (idx++) << std::endl;
            for (std::size_t i = node.begin; i<node.end; i++) {
                int curr_clazz = dr.records_classes[dr.offsets[i]];
                auto tmp = (double)(dr.forthegain.countClass(curr_clazz));
                if (tmp > purity) {
                    purity = tmp;
                    clazz = curr_clazz;
                }
            }
            std::cerr << "normalizeCountClass " << (idx++) << std::endl;
            dr.forthegain.normalizeCountClass();
            const double current_weight = purity / ((double)dr.max_record_size);
            purity = purity/((double) N);
            bool terminate = false;
            if ((N<=dr.eta) || (purity >= dr.maxPrec) || (node.max_height == dr.max_height)) {
                std::cerr << "purityTerminate " << (idx++) << std::endl;
                terminate = true;
            } else {
                node.candidate.second = -1;

                dr.sortOnSelectedNumericField(numerical, node.begin, node.end, node.candidate, do_just_classical_same);
                dr.sortOnSelectedCategoricalField(categorical, node.begin, node.end, node.candidate);

                if (dooblique)
                    dr.sortOnSelectedObliquity(numerical, node.begin, node.end, node.candidate, 10);

                if (node.candidate.second == -1) {
                    std::cerr << "node.candidate.second == -1 " << (idx++)  << std::endl;
                    terminate = true;
                } else {
                    std::cerr << "re" << (idx++)  << std::endl;
                    dr.init_offsets(node.candidate.first.field, node.begin, node.end);
                    const union_minimal& missing_val = std::holds_alternative<double>(node.candidate.first.value) ? missing_val_dbl : missing_val_str;
                    auto beg = dr.offsets.begin()+node.begin;
                    auto end = dr.offsets.begin()+node.end;
                    auto it2 = std::stable_partition(beg,
                                                     end,
                                                     [&node,this,missing_val](const size_t& obj) {
                                                        if (this->dr.fieldOffset[obj] == -1) {
                                                            return node.candidate.first(missing_val);
                                                        }
//                                                         if (!(this->dr.records[obj][this->dr.fieldOffset[obj]].first == node.candidate.first.field))
//                                                             exit(199);
                                                         return node.candidate.first(this->dr.records[obj][this->dr.fieldOffset[obj]].second);
                                                     });
                    if ((it2 == beg) || (it2 == end)) {
                        std::cerr << "id beg/end Terminate" << std::endl;
                        terminate = true;
                    }
                    node.split = (size_t)((ptrdiff_t)(it2-dr.offsets.begin()));
                    currentNode.push(children.size());
                    children.emplace_back(node.begin, node.split, node.max_height+1);
                }
            }

            if (terminate) {
                std::cerr << "isTerminate "  << (idx++) << std::endl;
                node.isLeaf = true;
                node.majority_class = clazz;
                node.majority_class_precision = dr.forthegain.getClassPrecision(clazz);
                total_weights += current_weight;
                goodness += (node.majority_class_precision * current_weight);
                currentNode.pop();
                continue;
            }
        } else if (node.rightOffset == 0) {
            std::cerr << "node.rightOffset == 0 "  << (idx++) <<  std::endl;
            node.rightOffset = children.size();
            currentNode.push(node.rightOffset);
            children.emplace_back(node.split, node.end, node.max_height+1);
        } else {
            std::cerr << "pop "  << (idx++) <<  std::endl;
            currentNode.pop();
        }
    }

    if (total_weights > 0.0) {
        goodness = goodness / total_weights;
    }
}

void DecisionTree::populate_children_predicates2(size_t nodeid,
                                   std::unordered_map<int, std::vector<std::pair<double,std::vector<dt_predicate>>>> &decision_to_pred,
                                   std::vector<dt_predicate>& current_stack) /*const*/ {
    auto& node = children[nodeid];
    if (!node.isLeaf) {
        const auto sat_ptr = children[nodeid+1];
        const auto viol_ptr = children[node.rightOffset];

        {
            auto unsat_copy = current_stack;
            auto& cpy = unsat_copy.emplace_back(node.candidate.first);
            switch(cpy.pred){
                case dt_predicate::OBL_PREDICATE_LEQ:
                    cpy.pred = dt_predicate::OBL_PREDICATE_GT;
                    break;
                case dt_predicate::LEQ_THAN:
                    cpy.pred = dt_predicate::G_THAN;
                    break;
                case dt_predicate::IN_SET:
                    cpy.pred = dt_predicate::NOT_IN_SET;
                    break;
                case dt_predicate::L_THAN:
                case dt_predicate::G_THAN:
                case dt_predicate::GEQ_THAN:
                case dt_predicate::NOT_IN_SET:
                case dt_predicate::OBL_PREDICATE_GT:
                    /* We should never get here, assign copies only */
                    break;
            }
            populate_children_predicates2(node.rightOffset, decision_to_pred, unsat_copy);
        }
        {
            current_stack.emplace_back(node.candidate.first);
            populate_children_predicates2(nodeid+1,decision_to_pred, current_stack);
        }
    } else {
        auto& ref = children[nodeid];
        ref.leaf_class_result = current_stack;
        decision_to_pred[ref.majority_class].emplace_back(ref.majority_class_precision, current_stack);
    }
}

const Nodes* DecisionTree::prediction(const std::vector<std::pair<std::string,union_minimal>>& record) const {
    size_t nodeid = 0;
    const auto* node = &children[nodeid];
    while (!node->isLeaf) {
        if (node->candidate.first(record)) {
            nodeid = node->rightOffset;
        } else {
            nodeid = nodeid+1;
        }
        node = &children[nodeid];
    }
    return node;
}