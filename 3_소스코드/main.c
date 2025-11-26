#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//학습 항목 정보를 저장할 구조체 정의
#define MAX_NAME_LENGTH 50
#define FILENAME "progress_data.txt"

typedef struct {
    int id;
    char subject[MAX_NAME_LENGTH];//과목 이름을 넣을 공간
    int total_units; //전체분량(페이지 또는 챕터)
    int current_progress; //현재진도량
} LearningItem;

LearningItem items[100]; //최대 100개의 항목 저장
int item_count = 0; // 현재 저장된 항목 수
int next_id = 1; //항목 ID를 고유하게 부여하기 위한 변수

// --- 함수 선언---
void load_data(); //시작시 기존 데이터 불러오는 함수
void save_data(); // 데이터를 저장하는 함수
void display_menu(); // 메뉴 항목을 보여주는 함수
void add_item(); // 과목을 추가하는 함수
void view_items(); // 저장된 항목을 보여주는 함수
void update_progress(); // 진도율을 갱신하는 함수
void delete_item(); // 과목 항목을 지우는 함수
void calculate_and_display_stats(); //진도율을 계산하고 보여주는 함수

// --- 메인 함수 ---
int main() {
    load_data(); // 시작시 데이터 불러오기
    int choice;

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            //입력 오류 처리(문자 입력등)
            printf("\n 잘못된 입력입니다. 다시 시도해주세요.\n");
            while(getchar() != '\n'); //입력 버퍼 지우기
            continue;
        }

// switch case 문으로 각각 원하는 함수를 선택할 수 있도록 구성
        switch (choice) {
            case 1:
                add_item();
                break;
            case 2:
                view_items();
                break;
            case 3:
                update_progress();
                break;
            case 4:
                delete_item();
                break;
            case 5:
                calculate_and_display_stats();
                break;
            case 6:
                save_data(); //종료 전 데이터 저장
                printf("\n 데이터를 저장하고 프로그램을 종료합니다.\n");
                return 0; //프로그램 종료
            default:
                printf("\n 1부터 6까지 숫자를 입력해주세요. \n");
        }
    }

    return 0;
}

// --- 함수 구현 ---

// 메뉴표시
void display_menu() {
    printf("\n=== 학습 진도 관리 프로그램 ===\n");
    printf("1. 새로운 학습 항목 추가 \n");
    printf("2. 전체 항목 목록 보기 \n");
    printf("3. 진도 업데이트 \n");
    printf("4. 학습 항목 삭제 \n"); 
    printf("5. 진도율 통계 보기 \n"); 
    printf("6. 종료 및 저장 \n"); 
    printf("-------------------------------\n");
    printf("선 택 : ");
}

// 새로운 학습 항목 추가
void add_item() {
    if (item_count >= 100) {
        printf("\n 최대 항목 개수(100개)에 도달했습니다.\n");
        return;
    } //최대 항목의 개수가 100개를 넘어서면 배열의 크기보다 커지기 때문에 종료

    printf("\n--- 학습 항목 추가 ---\n");
    
    // ID 자동 할당 및 갱신
    items[item_count].id = next_id;
    
    printf("과목명 입력 (최대 %d자): ", MAX_NAME_LENGTH - 1);
    scanf(" %49[^\n]", items[item_count].subject); // 공백 포함 입력, 버퍼 오버플로우 방지. subject가 배열이기때문에 주소연산자를 안씀
   
    printf("전체 분량 (페이지or 챕터 수): ");
    scanf("%d", &items[item_count].total_units);

    printf("현재 진도: ");
    scanf("%d", &items[item_count].current_progress);
    
    // 진도 유효성 검사
	    if (items[item_count].current_progress > items[item_count].total_units) {
        items[item_count].current_progress = items[item_count].total_units;
    } else if (items[item_count].current_progress < 0) {
        items[item_count].current_progress = 0;
    }

    item_count++;
    printf("\n 항목이 성공적으로 추가되었습니다! ('%s' ID: %d)\n", items[item_count - 1].subject, items[item_count - 1].id);
    next_id++; // 다음 항목에 부여할 ID 증가
}

//  학습 항목 삭제
void delete_item() {
    int id, i;

    if (item_count == 0) {
        printf("\n 삭제할 학습 항목이 없습니다.\n");
        return;
    }

    view_items();
    printf("\n---  학습 항목 삭제 ---\n");
    printf("삭제할 항목의 ID를 입력하세요: ");
    scanf("%d", &id);

    int found_index = -1;
    for (i = 0; i < item_count; i++) {
        if (items[i].id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("\n 해당 ID(%d)를 가진 항목을 찾을 수 없습니다.\n", id);
        return;
    }

    // 항목 삭제: 삭제된 항목 위치부터 배열의 끝까지 데이터를 한 칸씩 앞으로 당김
    printf(" 과목명: '%s'을(를) 삭제합니다.\n", items[found_index].subject);
    
    for ( i = found_index; i < item_count - 1; i++) {
        items[i] = items[i + 1]; // 다음 항목의 내용을 현재 위치로 복사
    }

    item_count--; // 전체 항목 수 1 감소
    
    printf("\n 항목이 성공적으로 삭제되었습니다.\n");
}


// 전체 항목 목록 보기
void view_items() {
	
	int i;
    if (item_count == 0) {
        printf("\n 등록된 학습 항목이 없습니다.\n");
        return;
    }

    printf("\n=========================================================\n");
    printf("| ID | 과목명          | 전체 분량 | 현재 진도 | 진행률 |\n");
    printf("=========================================================\n");

    for ( i = 0; i < item_count; i++) {
        double percentage = 0.0;
        if (items[i].total_units > 0) {
            percentage = (double)items[i].current_progress / items[i].total_units * 100;
        }
        
        printf("| %-2d | %-15s | %-9d | %-9d | %5.2f%% |\n",
               items[i].id, 
               items[i].subject, 
               items[i].total_units, 
               items[i].current_progress, 
               percentage);
    }
    printf("=========================================================\n");
}

// 진도 업데이트
void update_progress() {
    int id, i, new_progress;
    
    if (item_count == 0) {
        printf("\n 업데이트할 학습 항목이 없습니다. 먼저 항목을 추가해 주세요.\n");
        return;
    }

    view_items();
    printf("\n--- 진도 업데이트 ---\n");
    printf("진도를 업데이트할 항목의 ID를 입력하세요: ");
    scanf("%d", &id);

    int found_index = -1;
    for ( i = 0; i < item_count; i++) {
        if (items[i].id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("\n 해당 ID(%d)를 가진 항목을 찾을 수 없습니다.\n", id);
        return;
    }
    
    printf(" 현재 진도: %d / %d\n", items[found_index].current_progress, items[found_index].total_units);
    printf("새로운 진도를 입력하세요: ");
    scanf("%d", &new_progress);

    if (new_progress < 0) {
        new_progress = 0;
    } else if (new_progress > items[found_index].total_units) {
        new_progress = items[found_index].total_units; // 전체 분량 초과 불가
    }

    items[found_index].current_progress = new_progress;
    printf("\n '%s' 항목의 진도가 %d로 업데이트되었습니다.\n", items[found_index].subject, new_progress);
}

// 전체 진도율 통계를 계산하고 출력하는 함수
void calculate_and_display_stats() {
	int i;
    if (item_count == 0) {
        printf("\n 등록된 학습 항목이 없어 통계를 계산할 수 없습니다.\n");
        return;
    }

    double max_progress_rate = 0.0;
    double min_progress_rate = 101.0; 
    double total_progress_rate = 0.0;
    int valid_items = 0; 

    printf("\n---  진도율 통계 ---\n");

    for ( i = 0; i < item_count; i++) {
        if (items[i].total_units > 0) {
            double current_rate = ((double)items[i].current_progress / items[i].total_units) * 100.0;

            // 최대 진도율 갱신
            if (current_rate > max_progress_rate) {
                max_progress_rate = current_rate;
            }

            // 최소 진도율 갱신
            if (current_rate < min_progress_rate) {
                min_progress_rate = current_rate;
            }
            
            total_progress_rate += current_rate;
            valid_items++;

        } else {
            // 전체 분량이 0인 항목은 통계에서 제외 (나누기 0 방지)
            printf("경고: '%s' 항목은 전체 분량이 0이어서 통계에서 제외됩니다.\n", items[i].subject);
        }
    }

    if (valid_items == 0) {
         printf("\n통계에 포함할 유효한 항목이 없습니다. (모든 항목의 전체 분량이 0입니다.)\n");
         return;
    }
    
    double average_progress_rate = total_progress_rate / valid_items;

    printf("\n");
    printf("======================================\n");
    printf("최대 진도율: %.2f%%\n", max_progress_rate);
    printf("최소 진도율: %.2f%%\n", min_progress_rate);
    printf("평균 진도율: %.2f%%\n", average_progress_rate);
    printf("======================================\n");
}


// 데이터 파일 저장
void save_data() {
    FILE *file = fopen(FILENAME, "wb"); 
    if (file == NULL) {
        printf("\n파일 저장에 실패했습니다: %s\n", FILENAME);
        return;
    }

    // item_count와 next_id를 포함하여 저장
    fwrite(&item_count, sizeof(int), 1, file);
    fwrite(&next_id, sizeof(int), 1, file);
    
    // 항목 배열 전체 저장
    fwrite(items, sizeof(LearningItem), item_count, file);

    fclose(file);
}

// 데이터 파일 불러오기
void load_data() {
    FILE *file = fopen(FILENAME, "rb"); 
    if (file == NULL) {
        printf("\n 저장된 진도 파일이 없습니다. 새롭게 시작합니다.\n");
        item_count = 0;
        next_id = 1; // 새 시작 시 next_id 초기화
        return;
    }

    // item_count와 next_id를 포함하여 불러오기
    if (fread(&item_count, sizeof(int), 1, file) != 1 || 
        fread(&next_id, sizeof(int), 1, file) != 1) {
        // 파일 읽기 실패 시 초기화
        item_count = 0;
        next_id = 1;
        printf("\n 저장된 파일 형식이 올바르지 않아 새롭게 시작합니다.\n");
        fclose(file);
        return;
    }
    
    // 항목 배열 전체 불러오기
    fread(items, sizeof(LearningItem), item_count, file);

    fclose(file);
    printf("\n %d개의 학습 항목을 성공적으로 불러왔습니다.\n", item_count);
}


    
    

       
   

            
    
