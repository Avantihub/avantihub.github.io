
## 待学习，CS工作流

https://www.cc98.org/topic/5807249

https://github.com/Qi-Zhan/vscode-vim-config/blob/main/settings.json

{
    "terminal.integrated.defaultProfile.osx": "fish",
    "editor.fontSize": 16,
    "terminal.integrated.fontSize": 18,
    "editor.fontFamily": "'Fira Code', Menlo, Monaco, 'Courier New', monospace",
    "editor.fontLigatures": true,
    "vim.normalModeKeyBindings": [
        // map g e to goto next problem / error
        {
            "before": ["g", "e"],
            "commands": [
                "editor.action.marker.nextInFiles"
            ]
        },
        // map g b to go back previous navigation
        {
            "before": ["g", "b"],
            "commands": [
                "workbench.action.navigateBack"
            ]
        },
        // map g f to go forward next navigation
        {
            "before": ["g", "f"],
            "commands": [
                "workbench.action.navigateForward"
            ]
        },
        {
            "before": [":"],
            "commands": [
                "workbench.action.showCommands"
            ],
            "silent": true
        },
        // map f h to fold current block
        {
            "before": ["f", "h"],
            "commands": [
                "editor.fold"
            ]
        },
        // map f u to unfold current block
        {
            "before": ["f", "u"],
            "commands": [
                "editor.unfold"
            ]
        },
        // map to f a fold all blocks
        {
            "before": ["f", "a"],
            "commands": [
                "editor.foldAll"
            ]
        },
        // map f f to find file by name
        {
            "before": ["f", "f"],
            "commands": [
                "workbench.action.quickOpen"
            ]
        },
        // map f s to find symbol by name
        {
            "before": ["f", "s"],
            "commands": [
                "workbench.action.gotoSymbol"
            ]
        },
        // map r to rename symbol
        {
            "before": ["r", "n"],
            "commands": [
                "editor.action.rename"
            ]
        },
        // map > to move editor next group
        {
            "before": [">"],
            "commands": [
                "workbench.action.moveEditorToNextGroup"
            ]
        },
        // map < to move editor previous group
        {
            "before": ["<"],
            "commands": [
                "workbench.action.moveEditorToPreviousGroup"
            ]
        },
        // map tab to move editor next group
        {
            "before": ["tab"],
            "commands": [
                "workbench.action.nextEditor"
            ]
        },
        // map leader + x to close editor
        {
            "before": ["<leader>", "x"],
            "commands": [
                "workbench.action.closeActiveEditor"
            ]
        },
        // map leader + h to enable/disable copilot
        {
            "before": ["<leader>", "h"],
            "commands": [
                "github.copilot.toggleCopilot"
            ]
        }
    ],
    "vim.insertModeKeyBindings": [
        // map jj to escape
        {
            "before": ["j", "j"],
            "after": ["<Esc>"]
        }
    ],
    "vim.visualModeKeyBindings": [
        {
            "before": [
                ">"
            ],
            "commands": [
                "editor.action.indentLines"
            ]
        },
        {
            "before": [
                "<"
            ],
            "commands": [
                "editor.action.outdentLines"
            ]
        }
    ],
    "vim.foldfix": true,
    "vim.highlightedyank.enable": true,
    "vim.leader": "<space>"
}