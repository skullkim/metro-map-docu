# Teamproject1 API document

모든 json응답은 아래의 common response와 같은 형태를 띄고 있기 때문에 세부 API 설명에서는 오직 key가 data인 부분만 서술한다. 이때 에러에 대한 응답의 경우 data는 빈 문자열을 가지며 그 대신 error가 에러 원인에 대한 객체를 가진다.

```jsx
{
    "status": number,
    "status_code": string,
    "request": {
        "path": string,
        "method": string,
        "params": object,
        "query": object,
    },
    "data": object
}
```

## 최소 비용 경로

GET /api/:pathTarget

pathTarget: cost(최소 비용) || time(최소 시간) || distance(최소 정거장)

query: from(type: string(5)), to(type: string(5))

parameter: pathTarget

사용처:

성공:

```json

"data": {
	"min_value": string,
	"path": [minCostPath[]](https://www.notion.so/minCostPath-7a3128027a854ba0b5341ef73a0f84c7)
}

```

```jsx
minCostPath: 
{
	"id": number,
	"station": string
}
```

실패:

```jsx
"data": "",
"error": {
	"message": string
}
```

## 최소 비용 경로(경유지)

GET /api/path/stopover/:pathTarget

pathTarget: cost(최소 비용) || time(최소 시간) || distance(최소 정거장)

query: from(type: string(5)), to(type: string(5))

parameter: pathTarget

사용처:

성공:

```json

"data": {
	"min_value": string,
	"path": [minCostPath[]](https://www.notion.so/minCostPath-7a3128027a854ba0b5341ef73a0f84c7)
}

```

```jsx
minCostPath: 
{
	"id": number,
	"station": string
}
```

실패:

```jsx
"data": "",
"error": {
	"message": string
}
```