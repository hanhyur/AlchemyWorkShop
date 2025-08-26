#include "AlchemyWorkshop.h"

#include <iostream>
#include <algorithm>

void AlchemyWorkshop::addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
    if (findRecipeByName(name)) {
        std::cout << ">> 오류: 동일한 이름의 물약 레시피가 이미 존재합니다." << std::endl;
        return;
    }
    recipes.push_back(PotionRecipe(name, ingredients));
    potionStock[name] = INITIAL_STOCK;
    std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다. (초기 재고: " << INITIAL_STOCK << "개)" << std::endl;
}

void AlchemyWorkshop::displayAllRecipes() const {
    if (recipes.empty()) {
        std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
        return;
    }
    std::cout << "-- - [전체 레시피 목록] -- - " << std::endl;
        for (const auto& recipe : recipes) {
            std::cout << "- 물약 이름: " << recipe.potionName << " (현재 재고: " << getPotionStock(recipe.potionName) << "개)" << std::endl;
            std::cout << "  > 필요 재료: ";
            for (size_t j = 0; j < recipe.ingredients.size(); ++j) {
                std::cout << recipe.ingredients[j] << (j < recipe.ingredients.size() - 1 ? ", " : "");
            }
            std::cout << std::endl;
        }
    std::cout << "---------------------------";
}


const PotionRecipe* AlchemyWorkshop::findRecipeByName(const std::string& name) const {
    for (const auto& recipe : recipes) {
        if (recipe.potionName == name) {
            return &recipe;
        }
    }
    return nullptr;
}

std::vector<const PotionRecipe*> AlchemyWorkshop::findRecipesByIngredient(const std::string& ingredient) const {
    std::vector<const PotionRecipe*> found;
    for (const auto& recipe : recipes) {
        if (std::find(recipe.ingredients.begin(), recipe.ingredients.end(), ingredient) != recipe.ingredients.end()) {
            found.push_back(&recipe);
        }
    }
    return found;
}


int AlchemyWorkshop::getPotionStock(const std::string& potionName) const {
    auto it = potionStock.find(potionName);
    if (it != potionStock.end()) {
        return it->second;
    }
    return 0;
}

bool AlchemyWorkshop::dispensePotion(const std::string& potionName) {
    auto it = potionStock.find(potionName);
    if (it == potionStock.end()) {
        std::cout << ">> 오류: 해당 이름의 물약을 찾을 수 없습니다." << std::endl;
        return false;
    }

    if (it->second > 0) {
        it->second--;
        std::cout << ">> 물약 '" << potionName << "' 1개를 지급했습니다. (남은 재고: " << it->second << "개)" << std::endl;
        return true;
    }
    else {
        std::cout << ">> '" << potionName << "'의 재고가 부족합니다." << std::endl;
        return false;
    }
}

bool AlchemyWorkshop::returnPotion(const std::string& potionName) {
    auto it = potionStock.find(potionName);
    if (it == potionStock.end()) {
        std::cout << ">> 오류: 해당 이름의 물약은 레시피에 존재하지 않아 반환할 수 없습니다." << std::endl;
        return false;
    }

    if (it->second < MAX_STOCK) {
        it->second++;
        std::cout << ">> 물약 '" << potionName << "' 1개를 반환받았습니다. (현재 재고: " << it->second << "개)" << std::endl;
        return true;
    }
    else {
        std::cout << ">> '" << potionName << "'의 재고가 가득 차 있어 더 이상 반환받을 수 없습니다. (최대 재고: " << MAX_STOCK << "개)" << std::endl;
        return false;
    }
}


void AlchemyWorkshop::displayRecipes(const std::vector<const PotionRecipe*>& foundRecipes) const {
    if (foundRecipes.empty()) {
        std::cout << ">> 검색 결과가 없습니다." << std::endl;
        return;
    }
    std::cout << "-- - [검색된 레시피 목록] -- - " << std::endl;
        for (const auto* recipePtr : foundRecipes) {
            std::cout << "- 물약 이름: " << recipePtr->potionName << " (현재 재고: " << getPotionStock(recipePtr->potionName) << "개)" << std::endl;
            std::cout << "  > 필요 재료: ";
            for (size_t j = 0; j < recipePtr->ingredients.size(); ++j) {
                std::cout << recipePtr->ingredients[j] << (j < recipePtr->ingredients.size() - 1 ? ", " : "");
            }
            std::cout << std::endl;
        }
    std::cout << "-----------------------------";
}