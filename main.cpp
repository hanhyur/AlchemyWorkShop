#include "AlchemyWorkshop.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

void printMenu() {
    std::cout << "연금술 공방 관리 시스템" << std::endl;
    std::cout << "1. 레시피 추가" << std::endl;
    std::cout << "2. 전체 레시피 보기" << std::endl;
    std::cout << "3. 물약 이름으로 레시피 검색" << std::endl;
    std::cout << "4. 재료로 레시피 검색" << std::endl;
    std::cout << "5. 물약 지급" << std::endl;
    std::cout << "6. 물약 반환" << std::endl;
    std::cout << "7. 종료" << std::endl;
    std::cout << "선택: ";
}

void handleAddRecipe(AlchemyWorkshop& workshop) {
    std::string name;
    std::cout << "--- 레시피 추가 ---" << std::endl;
    std::cout << "물약 이름: ";
    std::getline(std::cin, name);

    std::vector<std::string> ingredients_input;
    std::string ingredient;
    std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;
    while (true) {
        std::cout << "재료 입력: ";
        std::getline(std::cin, ingredient);
        if (ingredient == "끝") {
            break;
        }
        if (!ingredient.empty()) {
            ingredients_input.push_back(ingredient);
        }
    }

    if (!ingredients_input.empty() && !name.empty()) {
        workshop.addRecipe(name, ingredients_input);
    }
    else {
        std::cout << ">> 이름이나 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
    }
}

void handleSearchByName(const AlchemyWorkshop& workshop) {
    std::string name;
    std::cout << "--- 이름으로 검색 ---" << std::endl;
    std::cout << "검색할 물약 이름: ";
    std::getline(std::cin, name);

    const PotionRecipe* recipe = workshop.findRecipeByName(name);
    if (recipe) {
        workshop.displayRecipes({ recipe });
    }
    else {
        std::cout << ">> '" << name << "'에 해당하는 레시피를 찾을 수 없습니다." << std::endl;
    }
}

void handleSearchByIngredient(const AlchemyWorkshop& workshop) {
    std::string ingredient;
    std::cout << "--- 재료로 검색 ---" << std::endl;
    std::cout << "검색할 재료 이름: ";
    std::getline(std::cin, ingredient);

    std::vector<const PotionRecipe*> recipes = workshop.findRecipesByIngredient(ingredient);
    workshop.displayRecipes(recipes);
}

void handleDispensePotion(AlchemyWorkshop& workshop) {
    std::string name;
    std::cout << "--- 물약 지급 ---" << std::endl;
    std::cout << "지급할 물약 이름: ";
    std::getline(std::cin, name);
    workshop.dispensePotion(name);
}

void handleReturnPotion(AlchemyWorkshop& workshop) {
    std::string name;
    std::cout << "--- 물약 반환 ---" << std::endl;
    std::cout << "반환받을 물약 이름: ";
    std::getline(std::cin, name);
    workshop.returnPotion(name);
}

int main() {
    AlchemyWorkshop myWorkshop;
    int choice = 0;

    myWorkshop.addRecipe("체력 회복 물약", { "붉은 약초", "마력이 깃든 물", "빈 병"});
    myWorkshop.addRecipe("마나 회복 물약", { "푸른 약초", "마력이 깃든 물", "빈 병"});
    myWorkshop.addRecipe("투명화 물약", { "유령 버섯", "투명 가루", "빈 병"});

    while (true) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            handleAddRecipe(myWorkshop);
            break;
        case 2:
            myWorkshop.displayAllRecipes();
            break;
        case 3:
            handleSearchByName(myWorkshop);
            break;
        case 4:
            handleSearchByIngredient(myWorkshop);
            break;
        case 5:
            handleDispensePotion(myWorkshop);
            break;
        case 6:
            handleReturnPotion(myWorkshop);
            break;
        case 7:
            std::cout << "공방 문을 닫습니다..." << std::endl;
            return 0;
        default:
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}