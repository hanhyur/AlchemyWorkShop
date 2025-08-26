#pragma once

#include "PotionRecipe.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;
    std::map<std::string, int> potionStock;
    static const int MAX_STOCK = 3;
    static const int INITIAL_STOCK = 3;

public:
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients);
    void displayAllRecipes() const;

    const PotionRecipe* findRecipeByName(const std::string& name) const;
    std::vector<const PotionRecipe*> findRecipesByIngredient(const std::string& ingredient) const;

    int getPotionStock(const std::string& potionName) const;
    bool dispensePotion(const std::string& potionName);
    bool returnPotion(const std::string& potionName);

    void displayRecipes(const std::vector<const PotionRecipe*>& foundRecipes) const;
};