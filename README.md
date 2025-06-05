# Expense Tracking System

## Overview

The **Expense Tracking System** is a menu-driven application designed to track family expenses efficiently. It allows users to add, update, and delete expenses while maintaining a structured record of individuals, families, and their financial transactions. The system is implemented using **AVL trees**, **inorder traversals**, **file handling**, and **menu-driven interfaces** for efficient management and persistence of data.

## Features

- **User Management:** Add users with unique User IDs, names, and income details.
- **Expense Tracking:** Record expenses categorized into Rent, Utility, Grocery, Stationary, and Leisure.
- **Family Management:** Group users into families (1-4 members) and track their collective financials.
- **Sorted Storage:** AVL Trees and inorder traversal ensure data is always sorted and efficiently searchable.
- **Expense Analysis:**
  - Track **total expenses** and compare them with family income.
  - Retrieve **category-wise expense reports** sorted by individual contribution.
  - Identify the **highest expense day** for a family.
  - Retrieve **individual expense details** sorted by category in descending order.
- **Update and Delete Functionality:** Modify or remove users, families, and expenses with automatic updates across linked records.
- **File Handling:** Read initial datasets from files and output final data to another file.

## Data Structures Used

The application uses **AVL trees** for individuals, families, and expenses for efficient insertion, deletion, and lookup.

### 1. Individual Node
- User ID
- User Name
- Income

### 2. Family Node
- Family ID
- Family Name
- Set of individuals
- Total family income
- Total monthly family expense

### 3. Expense Node
- Expense ID
- User ID (reference)
- Expense Category
- Expense Amount
- Date of expense

## Functions Implemented

1. `addUser()` – Add a user sorted by User ID using AVL insertion.
2. `addExpense()` – Add an expense to a user and update family expense.
3. `createFamily()` – Create family with users and calculate total income/expense.
4. `update_or_delete_individual_Family_details()` – Update/delete individuals/families with consistency.
5. `update_delete_expense()` – Update/delete specific expenses and reflect changes.
6. `get_total_expense()` – Display total family expense and compare with income.
7. `get_categorical_expense(category)` – Display category-wise family and individual expenses.
8. `get_highest_expense_day()` – Identify date with the highest overall spending.
9. `get_individual_expense(userID)` – Show total and per-category expense for an individual.
10. `get_expense_in_period(Date1, Date2)` – Filter expenses in a date range.
11. `get_expense_in_range(expenseID1, expenseID2, userID)` – Get expenses in a specific ID range for a user.

## Example AVL Rotation Function

```c
void rotateRight(user_tree** r){
    user_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->left == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->left ;
        (*r)->left = temp->right ;
        temp->right = *r ;
    }
    *r = temp;
}
```
## 🚀 Future Enhancements

- 🔹 **Graphical User Interface (GUI):** Implement a Tkinter-based desktop app or a web dashboard for improved user interaction.
- 🔹 **Database Integration:** Replace in-memory storage with MySQL or SQLite for persistent, scalable data management.
- 🔹 **Expense Trends & Reports:** Integrate data visualization tools to generate monthly spending charts and summaries.
- 🔹 **Export & Import Data:** Enable users to backup and restore data using CSV or JSON files.
- 🔹 **User Authentication:** Add login and role-based access for secure and personalized expense tracking.


