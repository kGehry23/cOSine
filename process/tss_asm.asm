global _set_task_register

; Loads the task register
_set_task_register:
    ltr [esp + 4]
    ret