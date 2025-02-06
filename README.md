# Football Tournament Management System

A tournament management system optimized for the Algerian League implementing balanced tree data structures and efficient algorithms for data processing implemented with C++.

## Architecture

### Core Components
- **Player**: Stack-based history tracking, O(1) statistic updates
- **Team**: DLL implementation, 23-player constraint
- **Game**: Match state management 
- **Round**: DLL for games/teams collections
- **Championship**: Dual implementation (BST/AVL)

### Data Structures
- BST/AVL Trees: Championship management
- Doubly Linked Lists: Team rosters, round organization
- Stacks: Player history tracking
- Priority Queues: Statistics rankings

## Technical Features
- Self-balancing AVL implementation
- O(1) player statistic updates
- O(log n) championship queries
- Efficient memory management
- Linear time team operations

## Performance Metrics
- BST Operations: ~115ms
- AVL Operations: ~109ms
- Memory Footprint: O(n) space complexity

## Testing Environment
- Dataset: 20 teams
- Sample Size: 3 rounds
- Test Coverage: 4 teams' historical data

## Dependencies
- C++ STL Collections
- Implementation requires C++11 or higher

