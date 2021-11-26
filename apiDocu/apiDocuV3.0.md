# Teamproject1 API document

모든 json응답은 아래의 common response와 같은 형태를 띄고 있기 때문에 세부 API 설명에서는 오직 key가 data인 부분만 서술한다. 이때 에러에 대한 응답의 경우 data는 빈 문자열을 가지며 그 대신 error가 에러 원인에 대한 객체를 가진다. 만약 키값 뒤에 '?'가 온다면 일부 응답에 대해 해당 값이 존재하지 않을 수 도 있다는 의미이다.

common response:

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
  "error"?: object
}
```

엑세스 토큰을 사용해 유저를 사전에 인증해야 하는 요청(헤더에 Authentication이 요구되는 요청)에서 토큰관련에러는 공통적으로 다음과 같은 응답을 한다. 따라서 아래의 API 중 토큰관련 에러가 응답으로 주어질 경우 '토큰 에러'로만 명시를 한다.

실패:(401-유효하지 않은 Authentication 헤더 데이터 형식 또는 유효하지 않은 토큰),

실패(403-엑세스 토큰 만료)

```jsx
"data": "",
"error": {
  "message": string
}
```

## 최소 비용 경로

GET /api/:pathTarget

pathTarget: cost(최소 비용) || time(최소 시간) || distance(최소 정거장)

query: startStation(type: string(3)), arriveStation(type: string(3))

parameter: pathTarget

사용처: src/components/modal/searchResultModal/SearchResultModal.js

성공(200):

```json

"data": {
  "cost": string,
  "distance": string,
  "time": string,
  "path": minPath[],
  "min_value"?: '',
  "other_value"?: {}
}

```

```jsx
minPath: 
{
  "id": number,
  "station": string
}
```

실패(400):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 최소 비용 경로(경유지)

GET /api/path/stopover/:pathTarget

pathTarget: cost(최소 비용) || time(최소 시간) || distance(최소 정거장)

query: startStation(type: string(3)), stopoverStation(type: string(3)), arriveStation(type: string(3))

parameter: pathTarget

사용처: src/components/modal/searchResultModal/SearchResultModal.js

성공(200):

```json

"data": {
  "time": string,
  "distance": string,
  "cost": string, 
  "path": minPath[]
}

```

```jsx
minPath: 
{
  "id": number,
  "station": string
}
```

실패(400):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 회원가입

POST /api/authentication/signup

body: email(string), password(string, 8자이상, 숫자, 문자, 특수문자 포함)

사용처: src/components/user/ValidateUserAccount.js

성공(201):

```jsx
"data": {
  "message": "success"
}
```

실패(400):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 회원가입 이메일 인증

GET /api/authentication/signup/email

query: key(string), id(string)

사용처: 발송된 이메일 내부

성공(200):

```jsx
"data": {
  "message": "success"
}
```

실패(403):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 회원가입 이메일 재인증

POST /api/authentication/signup/email/reauthorization

body: email(string)

사용처: src/components/user/ValidateUserAccount.js

성공(200):

```jsx
"data": {
  "message": "success"
}
```

실패(400-회원가입을 하지 않은 계정 또는 유효하지 않은 이메일 형식),

실패(409-이미 메일 인증을 한 유저):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 로그아웃

POST /api/authentication/logout

header: 'Bearer {accessToken}'

사용처:  src/components/user/Logout.js

성공(204):

```jsx
//응답 데이터 없음
```

실패: 토큰 에러

## 로그인

POST /api/authentication/signin

body: email(string), password(string)

사용처: src/components/user/ValidateUserAccount.js

성공(200):

```jsx
"data": {
  "user_id": number,
  "accessToken": string,
}
```

실패(400-유효하지 않은 이메일 형식 또는 비밀번호 형식. 또는 잘못된 비밀번호, 또는 가입하지 않은 계정),

실패(401-회원가입 인증메일 인증되지 않음):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 토큰 재발급

POST /api/authentication/refresh-token

사용처: src/lib/customAxios.js

성공(201):

```jsx
"data": {
  "accessToken": string,
}
```

실패: 토큰 에러

## 유저 검색기록 가져오기

GET /api/search-history/user/:userId

parameter: userId(number-user table pk)

header: Authentication: 'Bearer {accessToken}'

사용처:src/components/modal/searchHistoryModal/SearchHistoryModal.js

성공(200):

```jsx
"data": {
  "search_history": []
}
```

실패: 토큰 에러

## 유저 검색기록에서 저장한 북마크 수정

PUT /api/search-history/bookmark/:bookmarkId

parameter: bookmarkId(number-station_book_mark table pk)

header: Authentication: 'Bearer {accessToken}'

body: pathInfo(object- {from: string, to: string, stopover: string, target: string})

사용처: src/components/modal/searchHistoryModal/SerachHistoryModal.js

성공(204):

```jsx
"data": {}
```

실패: 토큰 에러

## 유저 북마크리스트 가져오기

GET /api/bookmark/user/:userId

parameter: userId(number-user table pk)

header: Authentication: 'Bearer {accessToken}'

사용처: src/pages/Bookmark.js

성공(200);

```jsx
"data": bookmark[]
```

```jsx
bookmark {
  "id": number,
  "from": string,
  "to": string,
  "stopover": string,
  "target": string
}
```

실패: 토큰 에러

## 유저 북마크리스트에서 특정 북마크 삭제

DELETE /api/bookmark/:bookmarkId/user/:userId

parameter: bookmarkId(number-station_book_mark table PK), userId(number-user table PK)

header: Authentication: 'Bearer {accessToken}'

body: pathInfo(object - {from: string, to: string, stopover: string, target: string})

사용처: src/pages/Bookmark.js

성공(204)

```jsx
"data": {}
```

실패: 토큰에서

## 유실물센터 정보 리스트 가져오기

GET /api/amenities/lost-and-found

사용처: src/components/amenities/LostAndFoundTable.js

성공(200)

```jsx
"data": lostAndFoundInfo[]
```

```jsx
lostAndFoundInfo {
  "id": number,
  "station": string,
  "callNumber": string,
  "operatingHour": string,
}
```

## 물품보관함 정보 리스트 가져오기

GET /api/amenities/store-box

사용처: src/components/amenities/StoreBoxTable.js

성공(200)

```jsx
"data": storeBoxInfo[]
```

```jsx
storeBoxInfo {
  "id": number,
  "station": string
}
```

## 민원 내용 메일로 발송하기

POST /api/amenities/user-complain

body: email(string), subwayLine(number), userComplainContext(string)

사용처: src/pages/userComplain.js

성공(204)

```jsx
//응답 데이터 없음
```

실패(400 - 유효하지 않은 이메일 형식, 민원 내용 길이 300자 이상 또는 10자 이하, 선택한 지하철 라인 수가 1~9사이가 아님):

```jsx
"data": "",
"error": {
  "message": string
}
```

## 유저 정보 수정하기

PUT /api/user/:userId/user-information

parameter: userId(number)

header: Authentication: 'Bearer {accessToken}'

body: email(string), previousPassword(string), newPassword(string)

사용처:

성공(204)

```jsx
//응답 데이터 없음
```

실패(400 - 유효하지 않은 이메일 형식, 같은 이메일이 이미 존재, 유효하지 않은 비밀번호 형식, 입력한 기존 비밀번호가 틀림)

```jsx
"data": "",
"error": {
  "message": string
}
```

실패: 토큰 에러

## 유저 이메일 가져오기

GET /api/user/:userId/email

parameter: userId(email)

header: Authentication: 'Bearer {accessToken}'

사용처:

성공(200)

```jsx
"data": string
```

실패: 토큰 에러