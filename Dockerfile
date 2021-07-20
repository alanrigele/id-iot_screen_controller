FROM alpine
RUN apk add --update nodejs nodejs-npm
#WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
EXPOSE 8000
CMD ["node", "index.js"]
