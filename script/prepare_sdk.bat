@echo off
SET cur_path=%CD%
FOR %%A IN ("%~dp0.") DO SET project_path=%%~dpA
SET esp_idf_path=%project_path%sdk\esp-idf

IF NOT DEFINED IDF_PATH %esp_idf_path%\export.bat

cd %cur_path%